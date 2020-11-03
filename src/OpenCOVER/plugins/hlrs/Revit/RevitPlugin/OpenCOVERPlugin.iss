; Script generated by the Inno Setup Script Wizard.
; SEE THE DOCUMENTATION FOR DETAILS ON CREATING INNO SETUP SCRIPT FILES!

#define ICONFILE GetEnv("COVISEDIR")+"/share/covise/icons/covise.ico"
#define COVISEDIR GetEnv("COVISEDIR")
#define EXTERNLIBS GetEnv("EXTERNLIBS")
#define ARCHSUFFIX GetEnv("ARCHSUFFIX")

#define REVIT_VERSION "2021"


[Setup]
;compiler-related
PrivilegesRequired=admin

OutputDir={#COVISEDIR+"\DIST"}    

OutputBaseFilename=HLRS_OpenCOVERPlugin_For_Revit_{#REVIT_VERSION}   
ArchitecturesInstallIn64BitMode="x64" 

;installer-related
AppName=OpenCOVERPlugin
AppVerName=OpenCOVER connection plugin for Revit {#REVIT_VERSION}
AppPublisher=HLRS
AppPublisherURL=http://www.hlrs.de
AppSupportURL=http://www.hlrs.de/covise
AppUpdatesURL=http://www.hlrs.de/covise/support/download

ChangesAssociations=false
ChangesEnvironment=false
DefaultDirName={autopf}\OpenCOVERPlugin
DefaultGroupName=VrmlExp
DisableStartupPrompt=false
; cosmetic
;#emit ICONFILE
SetupIconFile={#ICONFILE}
ShowLanguageDialog=yes


[Files]

Source: {#COVISEDIR}\{#ARCHSUFFIX}\lib\OpenCOVERPlugin.dll; DestDir: {app}

[UninstallDelete]
Type: files; Name: "{commonappdata}\Autodesk\Revit\Addins\{#REVIT_VERSION}\OpenCOVERPlugin.addin"

[Code]

program Setup;

procedure CurStepChanged(CurStep: TSetupStep);
var
fileName :String;
begin
  if CurStep = ssPostInstall then
  begin
   fileName :=    ExpandConstant('{commonappdata}')+'\Autodesk\Revit\Addins\{#REVIT_VERSION}\OpenCOVERPlugin.addin';  
   SaveStringToFile(fileName, '<?xml version="1.0" encoding="utf-8"?>'+ #13#10 +
'<RevitAddIns>'+ #13#10 +
'  <AddIn Type="Application"> '+ #13#10 +
'    <Name>COVERToolbar</Name>'+ #13#10 +
'    <Assembly>'+ ExpandConstant('{app}')+'\OpenCOVERPlugin.dll'+'</Assembly>'+ #13#10 +
'    <AddInId>10a97048-ef29-446a-a2ef-ad092b7cd2cf</AddInId>'+ #13#10 +
'    <FullClassName>OpenCOVERPlugin.COVERToolbar</FullClassName>'+ #13#10 +
'    <VendorId>HLRS</VendorId>'+ #13#10 +
'    <VendorDescription>www.hlrs.de</VendorDescription>'+ #13#10 +
'  </AddIn>'+ #13#10 +
'</RevitAddIns>' + #13#10, False);
  
  end;                      
end;


begin
end.
