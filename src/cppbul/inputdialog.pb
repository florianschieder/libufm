ProcedureCDLL.s cppbul_InputDialog(Title$, Text$, DefaultText$)
  ProcedureReturn InputRequester(Title$, Text$, DefaultText$)
EndProcedure

ProcedureCDLL.s cppbul_PasswordDialog(Title$, Text$)
  ProcedureReturn InputRequester(Title$, Text$, "", #PB_InputRequester_Password)
EndProcedure

; IDE Options = PureBasic 5.71 LTS (Windows - x64)
; CursorPosition = 4
; Folding = -
; EnableXP