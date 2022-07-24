#include <cmath>
#include <iostream>
#include <chrono>

#define TESTS 10

/*
in desktop with i5-4590S 3.00GHz, 4GB

mingw-w64 with x86_64-8.1.0-win32-seh-rt_v6-rev
mysqrt avg : 4667.81ms
stdlib avg : 10645.1ms
2.28times faster

MinGW-W64 x86_64-posix-seh, built by Brecht Sanders) 11.1.0
mysqrt avg : 4651.74ms
stdlib avg : 5255.95ms
1.13 tiems faster
*/
float fsqrt_(float f) {

	int i = *(int *)&f;
	i = (i >> 1) + 0x1fbb67ae;
	float f1 = *(float *)&i;
	return 0.5F * (f1 + f / f1);

}


double my_test() { 

	auto start = std::chrono::high_resolution_clock::now();

	float max = 0.0F;
	for (int i = 0x00800000 ; i < 0x7f800000 ; i++) {

		float f = *(float*) &i;
		float re = fsqrt_(f);
		if(max < re) max = re;

	}

	auto end1 = std::chrono::high_resolution_clock::now();

	std::cout << "mysqrt max : " << max << std::endl;
	return std::chrono::duration<double, std::milli>(end1 - start).count();
	
}

double lib_test() {

	auto start = std::chrono::high_resolution_clock::now();	

	float max = 0.0F;
	for (int i = 0x00800000 ; i < 0x7f800000 ; i++) {

		float f = *(float*) &i;
		float re = sqrtf(f);
		if(max < re) max = re;

	}

	auto end1 = std::chrono::high_resolution_clock::now();

	std::cout << "stdlib max : " << max << std::endl;
	return std::chrono::duration<double, std::milli>(end1 - start).count();
	
}


int main() {
    
	std::cout << "* warmup" << std::endl;
	for(int i = 0 ; i < 3 ; i++) {

		my_test();
		lib_test(); 
	}

	double my = 0.0, lib = 0.0;

	std::cout << "\n\n* test\n" << std::endl;
	for(int i = 0 ; i < TESTS ; i++) {

		my += my_test();
		lib += lib_test();

	}

	std::cout << "\n\nmysqrt avg : " << (my / TESTS) << "ms\nstdlib avg : " << (lib / TESTS) << "ms" << "\n";
	std::cout << "my sqrt is " << (lib/my) << " times faster than standard library" <<std::endl;

}


/* generated assembly code
In x86-64 clang 12.0.1 :

.LCPI0_0:
        .long   0x3f000000                      # float 0.5
fsqrt_(float):                             # @fsqrt_(float)
        push    rbp
        mov     rbp, rsp
        movss   dword ptr [rbp - 4], xmm0
        mov     eax, dword ptr [rbp - 4]
        mov     dword ptr [rbp - 8], eax
        mov     eax, dword ptr [rbp - 8]
        sar     eax, 1
        add     eax, 532375470
        mov     dword ptr [rbp - 8], eax
        movss   xmm0, dword ptr [rbp - 8]       # xmm0 = mem[0],zero,zero,zero
        movss   dword ptr [rbp - 12], xmm0
        movss   xmm1, dword ptr [rbp - 12]      # xmm1 = mem[0],zero,zero,zero
        movss   xmm0, dword ptr [rbp - 4]       # xmm0 = mem[0],zero,zero,zero
        divss   xmm0, dword ptr [rbp - 12]
        addss   xmm1, xmm0
        movss   xmm0, dword ptr [rip + .LCPI0_0] # xmm0 = mem[0],zero,zero,zero
        mulss   xmm0, xmm1
        pop     rbp
        ret



In x86-64 clang 11.0.1 :

.LCPI0_0:
        .long   0x3f000000                      # float 0.5
fsqrt_(float):                             # @fsqrt_(float)
        push    rbp
        mov     rbp, rsp
        movss   xmm1, dword ptr [rip + .LCPI0_0] # xmm1 = mem[0],zero,zero,zero
        movss   dword ptr [rbp - 4], xmm0
        mov     eax, dword ptr [rbp - 4]
        mov     dword ptr [rbp - 8], eax
        mov     eax, dword ptr [rbp - 8]
        sar     eax, 1
        add     eax, 532375470
        mov     dword ptr [rbp - 8], eax
        movss   xmm0, dword ptr [rbp - 8]       # xmm0 = mem[0],zero,zero,zero
        movss   dword ptr [rbp - 12], xmm0
        movss   xmm0, dword ptr [rbp - 12]      # xmm0 = mem[0],zero,zero,zero
        movss   xmm2, dword ptr [rbp - 4]       # xmm2 = mem[0],zero,zero,zero
        divss   xmm2, dword ptr [rbp - 12]
        addss   xmm0, xmm2
        mulss   xmm1, xmm0
        movaps  xmm0, xmm1
        pop     rbp
        ret




In x86-64 gcc 11.1 / 10.3 / 9.4 :

fsqrt_(float):
        push    rbp
        mov     rbp, rsp
        movss   DWORD PTR [rbp-20], xmm0
        lea     rax, [rbp-20]
        mov     eax, DWORD PTR [rax]
        mov     DWORD PTR [rbp-8], eax
        mov     eax, DWORD PTR [rbp-8]
        sar     eax
        add     eax, 532375470
        mov     DWORD PTR [rbp-8], eax
        lea     rax, [rbp-8]
        movss   xmm0, DWORD PTR [rax]
        movss   DWORD PTR [rbp-4], xmm0
        movss   xmm0, DWORD PTR [rbp-20]
        divss   xmm0, DWORD PTR [rbp-4]
        movaps  xmm1, xmm0
        addss   xmm1, DWORD PTR [rbp-4]
        movss   xmm0, DWORD PTR .LC0[rip]
        mulss   xmm0, xmm1
        pop     rbp
        ret
.LC0:
        .long   1056964608



In x86-64 gcc 4.9.4 :

fsqrt_(float):
        push    rbp
        mov     rbp, rsp
        movss   DWORD PTR [rbp-20], xmm0
        lea     rax, [rbp-20]
        mov     eax, DWORD PTR [rax]
        mov     DWORD PTR [rbp-8], eax
        mov     eax, DWORD PTR [rbp-8]
        sar     eax
        add     eax, 532375470
        mov     DWORD PTR [rbp-8], eax
        lea     rax, [rbp-8]
        mov     eax, DWORD PTR [rax]
        mov     DWORD PTR [rbp-4], eax
        movss   xmm0, DWORD PTR [rbp-20]
        divss   xmm0, DWORD PTR [rbp-4]
        addss   xmm0, DWORD PTR [rbp-4]
        movss   xmm1, DWORD PTR .LC0[rip]
        mulss   xmm0, xmm1
        pop     rbp
        ret
.LC0:
        .long   1056964608




In x64 msvc v19.29 VS16.10

__real@3f000000 DD 03f000000r             ; 0.5

i$ = 0
f1$ = 4
f$ = 32
float fsqrt_(float) PROC                                    ; fsqrt_
$LN3:
        movss   DWORD PTR [rsp+8], xmm0
        sub     rsp, 24
        mov     eax, DWORD PTR f$[rsp]
        mov     DWORD PTR i$[rsp], eax
        mov     eax, DWORD PTR i$[rsp]
        sar     eax, 1
        add     eax, 532375470                            ; 1fbb67aeH
        mov     DWORD PTR i$[rsp], eax
        movss   xmm0, DWORD PTR i$[rsp]
        movss   DWORD PTR f1$[rsp], xmm0
        movss   xmm0, DWORD PTR f$[rsp]
        divss   xmm0, DWORD PTR f1$[rsp]
        movss   xmm1, DWORD PTR f1$[rsp]
        addss   xmm1, xmm0
        movaps  xmm0, xmm1
        movss   xmm1, DWORD PTR __real@3f000000
        mulss   xmm1, xmm0
        movaps  xmm0, xmm1
        add     rsp, 24
        ret     0
float fsqrt_(float) ENDP
*/