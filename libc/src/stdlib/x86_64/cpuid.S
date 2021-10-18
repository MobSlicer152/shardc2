// AT&T wrapper for the CPUID instruction
// 
// Copyright 2021 MobSlicer152
// 
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
// 
//     http://www.apache.org/licenses/LICENSE-2.0
// 
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

.section .text

.global _cpuid
type _cpuid, @function
_cpuid:
	pushq %rbp
	movq %rsp, %rbp
	pushq %rbx

	// Back up the parameters in RCX and RDX
	pushq %rdx
	pushq %rcx

	// Put the values desired for RAX and RCX in the right places
	movq %rdi, %rax
	movq %rsi, %rcx

	// Call cpuid
	cpuid

	// Move the results into the pointers given
	popq %r11
	movq %rax, (%r11)
	popq %r11
	movq %rbx, (%r11)
	movq %rcx, (%r8)
	movq %rdx, (%r9)

	popq %rbx
	movq %rbp, %rsp
	popq %rbp
	ret
