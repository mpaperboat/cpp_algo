/*
\subsection*{Description}

Make system stack larger. Simply put this code before main function, and the system stack will be enlarged.

\subsection*{Fields}

\begin{tabu} to \textwidth {|X|X|}
\hline
\multicolumn{2}{|l|}{\bfseries{\#define STACK\_SIZE 64}}\\
\hline
\bfseries{Description} & the size of system stack in MB\\
\hline
\end{tabu}

\subsection*{Code}
*/#include<cstdlib>
using namespace std;
#define STACK_SIZE 64
#if __GNUC__
    #if __x86_64__||__ppc64__
        extern int _main(void)__asm__("_main");
    #else
        extern int _main(void)__asm__("__main");
    #endif
    int __main();
    int _main() {
        __main();
        exit(0);
    }
    int main(){
        __asm__ __volatile__(
            #if __x86_64__||__ppc64__
                "movq %0,%%rsp\n"
                "pushq $exit\n"
                "jmp _main\n"
            #else
                "movl %0,%%esp\n"
                "pushl $_exit\n"
                "jmp __main\n"
            #endif
                ::"r"((char*)malloc(STACK_SIZE<<20)+(STACK_SIZE<<20))
        );
    }
    #define main __main
#elif defined(_MSC_VER)
    #pragma comment(linker,"/STACK:1024000000,1024000000")
#endif