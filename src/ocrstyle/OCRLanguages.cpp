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

#include "OCRLanguages.h"
#include <QObject>

OCRLanguages::OCRLanguages()
{
    initLanguages();
}

/*
  Language name from ISO 639-2 code
  http://en.wikipedia.org/wiki/List_of_ISO_639-2_codes
  */
void OCRLanguages::initLanguages()
{
    m_languages["abk"] = QObject::tr("Abkhaz");
    m_languages["aar"] = QObject::tr("Afar");
    m_languages["afr"] = QObject::tr("Afrikaans");
    m_languages["aka"] = QObject::tr("Akan");
    m_languages["sqi"] = QObject::tr("Albanian");
    m_languages["amh"] = QObject::tr("Amharic");
    m_languages["ara"] = QObject::tr("Arabic");
    m_languages["arg"] = QObject::tr("Aragonese");
    m_languages["hye"] = QObject::tr("Armenian");
    m_languages["asm"] = QObject::tr("Assamese");
    m_languages["ava"] = QObject::tr("Avaric");
    m_languages["ave"] = QObject::tr("Avestan");
    m_languages["aym"] = QObject::tr("Aymara");
    m_languages["aze"] = QObject::tr("Azerbaijani");
    m_languages["bam"] = QObject::tr("Bambara");
    m_languages["bak"] = QObject::tr("Bashkir");
    m_languages["eus"] = QObject::tr("Basque");
    m_languages["bel"] = QObject::tr("Belarusian");
    m_languages["ben"] = QObject::tr("Bengali");
    m_languages["bih"] = QObject::tr("Bihari");
    m_languages["bis"] = QObject::tr("Bislama");
    m_languages["bos"] = QObject::tr("Bosnian");
    m_languages["bre"] = QObject::tr("Breton");
    m_languages["bul"] = QObject::tr("Bulgarian");
    m_languages["mya"] = QObject::tr("Burmese");
    m_languages["cat"] = QObject::tr("Catalan; Valencian");
    m_languages["cha"] = QObject::tr("Chamorro");
    m_languages["che"] = QObject::tr("Chechen");
    m_languages["nya"] = QObject::tr("Chichewa; Chewa; Nyanja");
    m_languages["zho"] = QObject::tr("Chinese");
    m_languages["chv"] = QObject::tr("Chuvash");
    m_languages["cor"] = QObject::tr("Cornish");
    m_languages["cos"] = QObject::tr("Corsican");
    m_languages["cre"] = QObject::tr("Cree");
    m_languages["hrv"] = QObject::tr("Croatian");
    m_languages["ces"] = QObject::tr("Czech");
    m_languages["dan"] = QObject::tr("Danish");
    m_languages["div"] = QObject::tr("Divehi; Dhivehi; Maldivian;");
    m_languages["nld"] = QObject::tr("Dutch");
    m_languages["dzo"] = QObject::tr("Dzongkha");
    m_languages["eng"] = QObject::tr("English");
    m_languages["epo"] = QObject::tr("Esperanto");
    m_languages["est"] = QObject::tr("Estonian");
    m_languages["ewe"] = QObject::tr("Ewe");
    m_languages["fao"] = QObject::tr("Faroese");
    m_languages["fij"] = QObject::tr("Fijian");
    m_languages["fin"] = QObject::tr("Finnish");
    m_languages["fra"] = QObject::tr("French");
    m_languages["ful"] = QObject::tr("Fula; Fulah; Pulaar; Pular");
    m_languages["glg"] = QObject::tr("Galician");
    m_languages["kat"] = QObject::tr("Georgian");
    m_languages["deu"] = QObject::tr("German");
    m_languages["ell"] = QObject::tr("Greek, Modern");
    m_languages["grn"] = QObject::tr("Guaran¨ª");
    m_languages["guj"] = QObject::tr("Gujarati");
    m_languages["hat"] = QObject::tr("Haitian; Haitian Creole");
    m_languages["hau"] = QObject::tr("Hausa");
    m_languages["heb"] = QObject::tr("Hebrew (modern)");
    m_languages["her"] = QObject::tr("Herero");
    m_languages["hin"] = QObject::tr("Hindi");
    m_languages["hmo"] = QObject::tr("Hiri Motu");
    m_languages["hun"] = QObject::tr("Hungarian");
    m_languages["ina"] = QObject::tr("Interlingua");
    m_languages["ind"] = QObject::tr("Indonesian");
    m_languages["ile"] = QObject::tr("Interlingue");
    m_languages["gle"] = QObject::tr("Irish");
    m_languages["ibo"] = QObject::tr("Igbo");
    m_languages["ipk"] = QObject::tr("Inupiaq");
    m_languages["ido"] = QObject::tr("Ido");
    m_languages["isl"] = QObject::tr("Icelandic");
    m_languages["ita"] = QObject::tr("Italian");
    m_languages["iku"] = QObject::tr("Inuktitut");
    m_languages["jpn"] = QObject::tr("Japanese");
    m_languages["jav"] = QObject::tr("Javanese");
    m_languages["kal"] = QObject::tr("Kalaallisut, Greenlandic");
    m_languages["kan"] = QObject::tr("Kannada");
    m_languages["kau"] = QObject::tr("Kanuri");
    m_languages["kas"] = QObject::tr("Kashmiri");
    m_languages["kaz"] = QObject::tr("Kazakh");
    m_languages["khm"] = QObject::tr("Khmer");
    m_languages["kik"] = QObject::tr("Kikuyu, Gikuyu");
    m_languages["kin"] = QObject::tr("Kinyarwanda");
    m_languages["kir"] = QObject::tr("Kirghiz, Kyrgyz");
    m_languages["kom"] = QObject::tr("Komi");
    m_languages["kon"] = QObject::tr("Kongo");
    m_languages["kor"] = QObject::tr("Korean");
    m_languages["kur"] = QObject::tr("Kurdish");
    m_languages["kua"] = QObject::tr("Kwanyama, Kuanyama");
    m_languages["lat"] = QObject::tr("Latin");
    m_languages["ltz"] = QObject::tr("Luxembourgish, Letzeburgesch");
    m_languages["lug"] = QObject::tr("Luganda");
    m_languages["lim"] = QObject::tr("Limburgish, Limburgan, Limburger");
    m_languages["lin"] = QObject::tr("Lingala");
    m_languages["lao"] = QObject::tr("Lao");
    m_languages["lit"] = QObject::tr("Lithuanian");
    m_languages["lub"] = QObject::tr("Luba-Katanga");
    m_languages["lav"] = QObject::tr("Latvian");
    m_languages["glv"] = QObject::tr("Manx");
    m_languages["mkd"] = QObject::tr("Macedonian");
    m_languages["mlg"] = QObject::tr("Malagasy");
    m_languages["msa"] = QObject::tr("Malay");
    m_languages["mal"] = QObject::tr("Malayalam");
    m_languages["mlt"] = QObject::tr("Maltese");
    m_languages["mri"] = QObject::tr("M¨¡ori");
    m_languages["mar"] = QObject::tr("Marathi (Mar¨¡?h¨©)");
    m_languages["mah"] = QObject::tr("Marshallese");
    m_languages["mon"] = QObject::tr("Mongolian");
    m_languages["nau"] = QObject::tr("Nauru");
    m_languages["nav"] = QObject::tr("Navajo, Navaho");
    m_languages["nob"] = QObject::tr("Norwegian Bokm?l");
    m_languages["nde"] = QObject::tr("North Ndebele");
    m_languages["nep"] = QObject::tr("Nepali");
    m_languages["ndo"] = QObject::tr("Ndonga");
    m_languages["nno"] = QObject::tr("Norwegian Nynorsk");
    m_languages["nor"] = QObject::tr("Norwegian");
    m_languages["iii"] = QObject::tr("Nuosu");
    m_languages["nbl"] = QObject::tr("South Ndebele");
    m_languages["oci"] = QObject::tr("Occitan");
    m_languages["oji"] = QObject::tr("Ojibwe, Ojibwa");
    m_languages["chu"] = QObject::tr("Old Church Slavonic, Church Slavic, Church Slavonic, Old Bulgarian, Old Slavonic");
    m_languages["orm"] = QObject::tr("Oromo");
    m_languages["ori"] = QObject::tr("Oriya");
    m_languages["oss"] = QObject::tr("Ossetian, Ossetic");
    m_languages["pan"] = QObject::tr("Panjabi, Punjabi");
    m_languages["pli"] = QObject::tr("P¨¡li");
    m_languages["fas"] = QObject::tr("Persian");
    m_languages["pol"] = QObject::tr("Polish");
    m_languages["pus"] = QObject::tr("Pashto, Pushto");
    m_languages["por"] = QObject::tr("Portuguese");
    m_languages["que"] = QObject::tr("Quechua");
    m_languages["roh"] = QObject::tr("Romansh");
    m_languages["run"] = QObject::tr("Kirundi");
    m_languages["ron"] = QObject::tr("Romanian, Moldavian, Moldovan");
    m_languages["rus"] = QObject::tr("Russian");
    m_languages["san"] = QObject::tr("Sanskrit (Sa?sk?ta)");
    m_languages["srd"] = QObject::tr("Sardinian");
    m_languages["snd"] = QObject::tr("Sindhi");
    m_languages["sme"] = QObject::tr("Northern Sami");
    m_languages["smo"] = QObject::tr("Samoan");
    m_languages["sag"] = QObject::tr("Sango");
    m_languages["srp"] = QObject::tr("Serbian");
    m_languages["gla"] = QObject::tr("Scottish Gaelic; Gaelic");
    m_languages["sna"] = QObject::tr("Shona");
    m_languages["sin"] = QObject::tr("Sinhala, Sinhalese");
    m_languages["slk"] = QObject::tr("Slovak");
    m_languages["slv"] = QObject::tr("Slovene");
    m_languages["som"] = QObject::tr("Somali");
    m_languages["sot"] = QObject::tr("Southern Sotho");
    m_languages["spa"] = QObject::tr("Spanish; Castilian");
    m_languages["sun"] = QObject::tr("Sundanese");
    m_languages["swa"] = QObject::tr("Swahili");
    m_languages["ssw"] = QObject::tr("Swati");
    m_languages["swe"] = QObject::tr("Swedish");
    m_languages["tam"] = QObject::tr("Tamil");
    m_languages["tel"] = QObject::tr("Telugu");
    m_languages["tgk"] = QObject::tr("Tajik");
    m_languages["tha"] = QObject::tr("Thai");
    m_languages["tir"] = QObject::tr("Tigrinya");
    m_languages["bod"] = QObject::tr("Tibetan Standard, Tibetan, Central");
    m_languages["tuk"] = QObject::tr("Turkmen");
    m_languages["tgl"] = QObject::tr("Tagalog");
    m_languages["tsn"] = QObject::tr("Tswana");
    m_languages["ton"] = QObject::tr("Tonga (Tonga Islands)");
    m_languages["tur"] = QObject::tr("Turkish");
    m_languages["tso"] = QObject::tr("Tsonga");
    m_languages["tat"] = QObject::tr("Tatar");
    m_languages["twi"] = QObject::tr("Twi");
    m_languages["tah"] = QObject::tr("Tahitian");
    m_languages["uig"] = QObject::tr("Uighur, Uyghur");
    m_languages["ukr"] = QObject::tr("Ukrainian");
    m_languages["urd"] = QObject::tr("Urdu");
    m_languages["uzb"] = QObject::tr("Uzbek");
    m_languages["ven"] = QObject::tr("Venda");
    m_languages["vie"] = QObject::tr("Vietnamese");
    m_languages["vol"] = QObject::tr("Volap¨¹k");
    m_languages["wln"] = QObject::tr("Walloon");
    m_languages["cym"] = QObject::tr("Welsh");
    m_languages["wol"] = QObject::tr("Wolof");
    m_languages["fry"] = QObject::tr("Western Frisian");
    m_languages["xho"] = QObject::tr("Xhosa");
    m_languages["yid"] = QObject::tr("Yiddish");
    m_languages["yor"] = QObject::tr("Yoruba");
    m_languages["zha"] = QObject::tr("Zhuang, Chuang");
    m_languages["zul"] = QObject::tr("Zulu");
    m_languages["chi_sim"] = QObject::tr("Chinese (Simplified)");
    m_languages["chi_tra"] = QObject::tr("Chinese (Traditional)");
    m_languages["dan-frak"] = QObject::tr("Danish (Fraktur)");
    m_languages["deu-frak"] = QObject::tr("German (Fraktur)");
    m_languages["slk-frak"] = QObject::tr("Slovak (Fraktur)");
    m_languages["swe-frak"] = QObject::tr("Swedish (Fraktur)");
}

QString OCRLanguages::name(QString alias)
{
    if (m_languages.contains(alias))
        return m_languages[alias];

    return "";
}
