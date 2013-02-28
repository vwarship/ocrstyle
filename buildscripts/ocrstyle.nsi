; 安装程序初始定义常量
!define OCRSTYLE_NAME "ocrstyle.exe"
!define PRODUCT_NAME "OCR Style"
!define PRODUCT_VERSION "1.0"
!define PRODUCT_PUBLISHER "王军建"
!define PRODUCT_WEB_SITE "http://www.ocrstyle.com/"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\${OCRSTYLE_NAME}"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

; ------ MUI 现代界面定义 (1.67 版本以上兼容) ------
!include "MUI.nsh"

; MUI 预定义常量
!define MUI_ABORTWARNING
!define MUI_ICON "ocrstyle\ocrstyle.ico"
!define MUI_UNICON "ocrstyle\uninstall.ico"
!define MUI_WELCOMEFINISHPAGE_BITMAP "ocrstyle\welcome.bmp"
!define MUI_CUSTOMFUNCTION_GUIINIT MyGUIInit

; 欢迎页面
!insertmacro MUI_PAGE_WELCOME
; 许可协议页面
!insertmacro MUI_PAGE_LICENSE "ocrstyle\licence.txt"
; 安装目录选择页面
!insertmacro MUI_PAGE_DIRECTORY
; 安装过程页面
!insertmacro MUI_PAGE_INSTFILES
; 安装完成页面
!define MUI_FINISHPAGE_RUN "$INSTDIR\${OCRSTYLE_NAME}"
!insertmacro MUI_PAGE_FINISH

; 安装卸载过程页面
!insertmacro MUI_UNPAGE_INSTFILES

; 安装界面包含的语言设置
!insertmacro MUI_LANGUAGE "SimpChinese"

; 安装预释放文件
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; ------ MUI 现代界面定义结束 ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "${OCRSTYLE_NAME}"
InstallDir "$PROGRAMFILES\OCR Style"
InstallDirRegKey HKLM "${PRODUCT_UNINST_KEY}" "UninstallString"
ShowInstDetails show
ShowUnInstDetails show
BrandingText "OCR Style www.ocrstyle.com"

;BGGradient 000000 800000 FFFFFF
;InstallColors FF8080 000030
; 启用 WindowsXP 的视觉样式
XPstyle on

Section "MainSection" SEC01
	;判断文件是否已经安装
	IfFileExists "$INSTDIR\uninst.exe" +1 BEGIN_INSTALL
	  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您的系统已经安装了软件，确认要覆盖？" IDYES INSTALL_BEFORE_CHECK IDNO END_INSTALL

	;判断文件是否在运行
	INSTALL_BEFORE_CHECK:
  FindProcDLL::FindProc "${OCRSTYLE_NAME}"
    IntCmp $R0 1 TIP_CHECKED BEGIN_INSTALL
  TIP_CHECKED:
     MessageBox MB_ICONINFORMATION|MB_ABORTRETRYIGNORE "检测到 OCR Style 正在运行！$\r$\n终止：退出安装程序；$\r$\n忽略：强制结束进程并继续安装。" /SD IDABORT IDRETRY INSTALL_BEFORE_CHECK IDIGNORE IGNORE_RUN
     Quit
  IGNORE_RUN:
	  FindProcDLL::FindProc "${OCRSTYLE_NAME}"
	    IntCmp $R0 1 +1 BEGIN_INSTALL
  		KillProcDLL::KillProc "${OCRSTYLE_NAME}"

	BEGIN_INSTALL:
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  CreateDirectory "$SMPROGRAMS\OCR Style"
  CreateShortCut "$SMPROGRAMS\OCR Style\OCR Style.lnk" "$INSTDIR\${OCRSTYLE_NAME}"
  CreateShortCut "$DESKTOP\OCR Style.lnk" "$INSTDIR\${OCRSTYLE_NAME}"
  File "ocrstyle\licence.txt"
  File "..\bin\${OCRSTYLE_NAME}"
  File "..\bin\ocrengine.dll"
  File "..\bin\imageprocess.dll"
  File "..\bin\zlibwapi.dll"
  SetOutPath "$INSTDIR\tessdata"
  File /r /x ".svn" "..\bin\tessdata\*.*"
  SetOutPath "$INSTDIR\picture"
  File /r /x ".svn" "..\bin\picture\*.*"
  SetOutPath "$INSTDIR"

	END_INSTALL:
SectionEnd

Section -AdditionalIcons
  CreateShortCut "$SMPROGRAMS\OCR Style\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\${OCRSTYLE_NAME}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\${OCRSTYLE_NAME}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function .onInit
FunctionEnd

Function MyGUIInit
  #InitPluginsDir
	#File /oname=$PLUGINSDIR\splash.bmp "ocrstyle\splash.bmp"
	#BgImage::SetBg /FILLSCREEN $PLUGINSDIR\splash.bmp
	#CreateFont $R0 "Arial" 44 700 /ITALIC
	#BgImage::AddText "${PRODUCT_NAME} ${PRODUCT_VERSION}" $R0 255 255 255 40 48 1000 200
	#BgImage::Redraw
FunctionEnd

Function .onGUIEnd
	#BgImage::Destroy
FunctionEnd

/******************************
 *  以下是安装程序的卸载部分  *
 ******************************/

Section Uninstall
	;判断文件是否在运行
  FindProcDLL::FindProc "${OCRSTYLE_NAME}"
    IntCmp $R0 1 TIP_QUIT BEGIN_UNINSTALL

  TIP_QUIT:
    MessageBox MB_ICONSTOP " OCR Style 正在运行，请先关闭程序再进行卸载！"
    Quit
  
  BEGIN_UNINSTALL:
	; 卸载组件
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\${OCRSTYLE_NAME}"
  Delete "$INSTDIR\ocrengine.dll"
  Delete "$INSTDIR\imageprocess.dll"
  Delete "$INSTDIR\zlibwapi.dll"
  Delete "$INSTDIR\licence.txt"
  RMDir /r "$INSTDIR\tessdata"
  RMDir /r "$INSTDIR\picture"

  Delete "$SMPROGRAMS\OCR Style\Uninstall.lnk"
  Delete "$DESKTOP\OCR Style.lnk"
  Delete "$SMPROGRAMS\OCR Style\OCR Style.lnk"

  RMDir "$SMPROGRAMS\OCR Style"

  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd

#-- 根据 NSIS 脚本编辑规则，所有 Function 区段必须放置在 Section 区段之后编写，以避免安装程序出现未可预知的问题。--#

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "您确实要完全移除 $(^Name) ，及其所有的组件？" IDYES +2
  Abort
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从您的计算机移除。"
FunctionEnd
