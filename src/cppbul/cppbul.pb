XIncludeFile "messagebox.pb"
XIncludeFile "inputdialog.pb"

ProcedureCDLL cppbul_Init()
  UseBriefLZPacker()
  UseLZMAPacker()
  UseTARPacker()
  UseZipPacker()
EndProcedure

; IDE Options = PureBasic 5.71 LTS (Windows - x64)
; CursorPosition = 2
; Folding = -
; EnableXP