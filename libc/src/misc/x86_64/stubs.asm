;  Security cookie check, because MSVC generates code that clobbers the return
;  value of the function being checked
; 
;  Copyright 2021 MobSlicer152
; 
;  Licensed under the Apache License, Version 2.0 (the "License");
;  you may not use this file except in compliance with the License.
;  You may obtain a copy of the License at
; 
;      http://www.apache.org/licenses/LICENSE-2.0
; 
;  Unless required by applicable law or agreed to in writing, software
;  distributed under the License is distributed on an "AS IS" BASIS,
;  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
;  See the License for the specific language governing permissions and
;  limitations under the License.

OPTION PROLOGUE:NONE

EXTERN __security_cookie:QWORD
EXTERN _Exit:PROC

.code

__security_check_cookie PROC
	push rbp
	mov rbp, rsp
	
	; Get the security cookie and check it against this one
	mov r10, __security_cookie
	cmp rcx, r10
	jne die

	leave
	ret

	; Exit
	die:
		mov rcx, 69
		call _Exit
__security_check_cookie ENDP
PUBLIC __security_check_cookie

END

