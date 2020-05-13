ProcedureCDLL cppbul_MessageBox_Error(Title$, Text$)
  MessageRequester(Title$, Text$, #PB_MessageRequester_Error)
EndProcedure

ProcedureCDLL cppbul_MessageBox_Information(Title$, Text$)
  MessageRequester(Title$, Text$, #PB_MessageRequester_Info)
EndProcedure

ProcedureCDLL cppbul_MessageBox_Warning(Title$, Text$)
  MessageRequester(Title$, Text$, #PB_MessageRequester_Warning)
EndProcedure

ProcedureCDLL cppbul_MessageBox_Error_YesNo(Title$, Text$)
  result = MessageRequester(Title$, Text$, #PB_MessageRequester_Error | #PB_MessageRequester_YesNo)
  
  Select result
    Case #PB_MessageRequester_Yes
      ProcedureReturn 1
    Case #PB_MessageRequester_No
      ProcedureReturn 0
  EndSelect
EndProcedure

ProcedureCDLL cppbul_MessageBox_Information_YesNo(Title$, Text$)
  result = MessageRequester(Title$, Text$, #PB_MessageRequester_Info | #PB_MessageRequester_YesNo)
  
  Select result
    Case #PB_MessageRequester_Yes
      ProcedureReturn 1
    Case #PB_MessageRequester_No
      ProcedureReturn 0
  EndSelect
EndProcedure

ProcedureCDLL cppbul_MessageBox_Warning_YesNo(Title$, Text$)
  result = MessageRequester(Title$, Text$, #PB_MessageRequester_Warning | #PB_MessageRequester_YesNo)
  
  Select result
    Case #PB_MessageRequester_Yes
      ProcedureReturn 1
    Case #PB_MessageRequester_No
      ProcedureReturn 0
  EndSelect
EndProcedure

ProcedureCDLL cppbul_MessageBox_Error_YesNoCancel(Title$, Text$)
  result = MessageRequester(Title$, Text$, #PB_MessageRequester_Error | #PB_MessageRequester_YesNoCancel)
  
  Select result
    Case #PB_MessageRequester_Yes
      ProcedureReturn 1
    Case #PB_MessageRequester_No
      ProcedureReturn 0
    Case #PB_MessageRequester_Cancel
      ProcedureReturn -1
  EndSelect
EndProcedure

ProcedureCDLL cppbul_MessageBox_Information_YesNoCancel(Title$, Text$)
  result = MessageRequester(Title$, Text$, #PB_MessageRequester_Info | #PB_MessageRequester_YesNoCancel)
  
  Select result
    Case #PB_MessageRequester_Yes
      ProcedureReturn 1
    Case #PB_MessageRequester_No
      ProcedureReturn 0
    Case #PB_MessageRequester_Cancel
      ProcedureReturn -1
  EndSelect
EndProcedure

ProcedureCDLL cppbul_MessageBox_Warning_YesNoCancel(Title$, Text$)
  result = MessageRequester(Title$, Text$, #PB_MessageRequester_Warning | #PB_MessageRequester_YesNoCancel)
  
  Select result
    Case #PB_MessageRequester_Yes
      ProcedureReturn 1
    Case #PB_MessageRequester_No
      ProcedureReturn 0
    Case #PB_MessageRequester_Cancel
      ProcedureReturn -1
  EndSelect
EndProcedure

; IDE Options = PureBasic 5.71 LTS (Windows - x64)
; CursorPosition = 83
; FirstLine = 55
; Folding = --
; EnableXP