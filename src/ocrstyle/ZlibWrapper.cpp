// Copyright 2013, Zaoqibu Inc.
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
//     * Redistributions of source code must retain the above copyright
// notice, this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above
// copyright notice, this list of conditions and the following disclaimer
// in the documentation and/or other materials provided with the
// distribution.
//     * Neither the name of Zaoqibu Inc. nor the names of its
// contributors may be used to endorse or promote products derived from
// this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
//
// Author: vwarship@163.com (Junjian Wang)
//
// The Optical Character Recognition (OCR Style)

#ifdef __APPLE__
#define FOPEN_FUNC(filename, mode) fopen(filename, mode)
#define FTELLO_FUNC(stream) ftello(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko(stream, offset, origin)
#else
#define FOPEN_FUNC(filename, mode) fopen64(filename, mode)
#define FTELLO_FUNC(stream) ftello64(stream)
#define FSEEKO_FUNC(stream, offset, origin) fseeko64(stream, offset, origin)
#endif

#include "ZlibWrapper.h"
#include <direct.h>

#define WRITEBUFFERSIZE (8192)

ZlibWrapper::ZlibWrapper()
{
}

bool ZlibWrapper::uncompress(char *zipfilename)
{
    unzFile uf = NULL;

    if (zipfilename)
    {
        uf = unzOpen64(zipfilename);
    }

    bool ret = true;
    if (uf)
    {
        _chdir("tessdata");

        ret = doExtract(uf, NULL);
        unzClose(uf);

        _chdir("..");
    }

    return ret;
}

bool ZlibWrapper::doExtract(unzFile uf, const char* password)
{
    unz_global_info64 gi;
    if (unzGetGlobalInfo64(uf, &gi) != UNZ_OK)
        return false;

    for (uLong i=0; i<gi.number_entry; ++i)
    {
        if (doExtractCurrentfile(uf, password) != UNZ_OK)
        {
            break;
        }

        if ((i+1) < gi.number_entry)
        {
            if (unzGoToNextFile(uf) != UNZ_OK)
                break;
        }
    }

    return true;
}

int ZlibWrapper::doExtractCurrentfile(unzFile uf, const char* password)
{
    unz_file_info64 file_info = {0};
    char filename_inzip[256] = "\0";
    int err = unzGetCurrentFileInfo64(uf,&file_info,filename_inzip,sizeof(filename_inzip),NULL,0,NULL,0);

    if (err!=UNZ_OK)
    {
        return err;
    }

    uInt size_buf = WRITEBUFFERSIZE;
    void* buf = (void*)malloc(size_buf);
    if (buf==NULL)
    {
        return UNZ_INTERNALERROR;
    }

    const char* write_filename = filename_inzip;
    int skip=0;

    err = unzOpenCurrentFilePassword(uf,password);
    if (err!=UNZ_OK)
    {
        printf("error %d with zipfile in unzOpenCurrentFilePassword\n",err);
    }

    FILE *fout=NULL;
    if ((skip==0) && (err==UNZ_OK))
    {
        fout=FOPEN_FUNC(write_filename,"wb");
        if (fout==NULL)
        {
            printf("error opening %s\n",write_filename);
        }
    }

    if (fout!=NULL)
    {
        do
        {
            err = unzReadCurrentFile(uf,buf,size_buf);
            if (err<0)
            {
                printf("error %d with zipfile in unzReadCurrentFile\n",err);
                break;
            }

            if (err>0)
            {
                if (fwrite(buf,err,1,fout)!=1)
                {
                    printf("error in writing extracted file\n");
                    err=UNZ_ERRNO;
                    break;
                }
            }
        } while (err>0);

        if (fout)
            fclose(fout);
    }

    if (err == UNZ_OK)
    {
        if (unzCloseCurrentFile(uf)!=UNZ_OK)
        {
            printf("error %d with zipfile in unzCloseCurrentFile\n",err);
        }
    }
    else
        unzCloseCurrentFile(uf); /* don't lose the error */

    free(buf);
    return err;
}
