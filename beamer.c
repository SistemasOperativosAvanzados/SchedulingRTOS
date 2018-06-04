#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include "RM_EDF.h"
#include "beamer.h"
#include <math.h>


int schedulingRTOSBeamer(int nTasks, int runRM, int aloneRM, int runEDF, int aloneEDF, int runLLF, int aloneLLF, int* nPeriods, int* nComputations){
    int i,j;
    FILE* fp;

    fp = fopen("schedulingRTOS.tex", "w");


    fprintf(fp,"\\documentclass[xcolor=table]{beamer}\n");
    fprintf(fp,"\\usepackage[T1]{fontenc} \n");
    fprintf(fp,"\\usepackage{lmodern}\n");
    fprintf(fp,"\\usepackage[spanish]{babel}\n");
    fprintf(fp,"\\usepackage{fancyhdr}\n");
    fprintf(fp,"\\usepackage{xcolor}\n");
    fprintf(fp,"\\usepackage{color}\n");
    fprintf(fp,"\\usepackage{dirtytalk}\n");
    fprintf(fp,"\\usepackage{graphicx}\n");
    fprintf(fp,"\\usepackage{booktabs}\n");

    fprintf(fp,"\\definecolor{dgreen}{rgb}{0.,0.6,0.}\n");
    fprintf(fp,"\\definecolor{WHITE}{RGB}{255,255,255}\n");
    fprintf(fp,"\\definecolor{amarillo}{RGB}{255,255,0}\n");
    fprintf(fp,"\\definecolor{gris}{RGB}{174,174,174}\n");
    fprintf(fp,"\\definecolor{ROJO}{RGB}{237,28,36}\n");
    fprintf(fp,"\\setbeamercolor{normal text}{bg=black!80}\n"); 
    fprintf(fp,"\\setbeamercolor{frametitle}{fg=black,bg=amarillo!20}\n");
    fprintf(fp,"\\setbeamercolor{subtitle}{fg=WHITE}\n");
    fprintf(fp,"\\setbeamercolor{section in head/foot}{bg=amarillo}\n");
    fprintf(fp,"\\setbeamercolor{author}{fg=WHITE}\n");
    fprintf(fp,"\\setbeamercolor{date in head/foot}{fg=amarillo}\n");

    fprintf(fp,"\\title{{\\color{WHITE} \\large \\textbf{INSTITUTO TECNOL\\'OGICO DE COSTA RICA}} \\\\ \\vspace{0.02cm} \n");
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{MAESTR\\'IA EN COMPUTACI\\'ON }} \\\\ \\vspace{0.02cm} \n");
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{SISTEMAS OPERATIVO AVANZADOS}} \\\\ \\vspace{0.02cm} \n");
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{PROYECTO 3: SCHEDULING EN TIEMPO REAL}} \\\\ \\vspace{0.02cm} \n");
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{I SEMESTRE  }}\\\\ \\vspace{0.02cm}\n"); 
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{PROFESOR}} \\\\ \\vspace{0.02cm}\n"); 
    fprintf(fp,"{\\color{WHITE} \\large DR. FRANCISCO J. TORRES ROJAS  } \\\\ \\vspace{0.02cm}\n"); 
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{GRUPO 40}} \\\\ \\vspace{0.01cm}\n");
    fprintf(fp,"{\\color{WHITE} \\large \\textbf{ESTUDIANTES} }} \n");  
    fprintf(fp,"\\color{WHITE} \\author{KATHY ANDRE\\'INA BRENES GUERRERO. \\\\ SAMUEL YOO.}\n");
    fprintf(fp,"\\date{\\em \\color{WHITE} \\today}\n");
    fprintf(fp,"\\begin{document}\n");
    fprintf(fp,"\\nonstopmode\n");
    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\titlepage portada\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{Rate Monotonic Schedulling}\n");
    fprintf(fp,"Scheduling Algorithms for Multiprogramming in a Hard-Real-Time Environment.\n");
    fprintf(fp,"\\\\Paper presentado por Liu y Layland en 1973.\n");
    fprintf(fp,"\\\\Es un algoritmo de schedulling din\\'amico, derivado de HPF - prioridades fijas.\n"); 
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\Se basa en lo siguiente:\n");  
    fprintf(fp,"\\\\ \\textit{Si la carga de trabajo es schedulable por alg\\'un algoritmo de prioridades est\\'aticas, con RM tambi\\'en ser\\'a schedulable.}\n");
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\La prioridad es directamente proporcional al rate de la tarea peri\\'odica.\n");
    fprintf(fp,"\\\\Es un algoritmo expropiativo, cuando una tarea llega a la cola de ready, se revisan prioridades y de ser necesario, se expropian recursos a la tarea que se est\\'a ejecutando.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{Rate Monotonic Schedulling - Condiciones necesarias}\n");
    fprintf(fp,"Scheduling Algorithms for Multiprogramming in a Hard-Real-Time Environment.\n");
    fprintf(fp,"\\\\Paper presentado por Liu y Layland en 1973.\n");
    fprintf(fp,"\\\\Es un algoritmo de schedulling din\\'amico, derivado de HPF - prioridades fijas.\n"); 
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\Se basa en lo siguiente:\n");  
    fprintf(fp,"\\\\ \\textit{Si la carga de trabajo es schedulable por alg\\'un algoritmo de prioridades est\\'aticas, con RM tambi\\'en ser\\'a schedulable.}\n");
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\La prioridad es directamente proporcional al rate de la tarea peri\\'odica.\n");
    fprintf(fp,"\\\\Es un algoritmo expropiativo, cuando una tarea llega a la cola de ready, se revisan prioridades y de ser necesario, se expropian recursos a la tarea que se est\\'a ejecutando.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{Earliest Deadline First}\n");
    fprintf(fp,"Analizado por Liu y Layland (1973).\n");
    fprintf(fp,"\\\\Algoritmo de schedulling din\\'amico, derivado de HPF - prioridades din\\'amicas.\n"); 
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\Algoritmo \\'optimo:\n");  
    fprintf(fp,"\\\\ \\textit{Si la carga de trabajo es schedulable por alg\\'un algoritmo de prioridades din\\'amicas, con EDF tambi\\'en ser\\'a schedulable.}\n");
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\Prioridad de una tarea inversamente proporcional al tiempo pendiente para que se cumpla el deadline de la tarea.\n");
    fprintf(fp,"\\\\Es un algoritmo expropiativo, cuando una tarea llega a la cola de ready se revisan prioridades y de ser necesario, se expropian recursos a la tarea que se est\\'a ejecutando.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{Earliest Deadline First - Condiciones necesarias}\n");
    fprintf(fp,"Analizado por Liu y Layland (1973).\n");
    fprintf(fp,"\\\\Algoritmo de schedulling din\\'amico, derivado de HPF - prioridades din\\'amicas.\n"); 
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\Algoritmo \\'optimo:\n");  
    fprintf(fp,"\\\\ \\textit{Si la carga de trabajo es schedulable por alg\\'un algoritmo de prioridades din\\'amicas, con EDF tambi\\'en ser\\'a schedulable.}\n");
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\Prioridad de una tarea inversamente proporcional al tiempo pendiente para que se cumpla el deadline de la tarea.\n");
    fprintf(fp,"\\\\Es un algoritmo expropiativo, cuando una tarea llega a la cola de ready se revisan prioridades y de ser necesario, se expropian recursos a la tarea que se est\\'a ejecutando.\n");
    fprintf(fp,"\\end{frame} \n");
    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    
    fprintf(fp,"\\frametitle{Least Laxity First (LLF)}\n");
    fprintf(fp,"Tambi\\'en conocido como Least Slack Time  algorithm (LST).\n");
    fprintf(fp,"\\\\Es un algoritmo de asignaci\\'on de prioridades basado en la holgura de tiempo (Slack time) de un proceso.\n"); 
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\Slack time es la cantidad de tiempo que queda despu\\'es de que se ejecut\\'o un proceso.\n");
    fprintf(fp,"\\\\Su uso m\\'as com\\'un es en sistemas integrados, especialmente aquellos con m\\'ultiples procesadores.\n");
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\Impone la restricci\\'on simple de que cada proceso en cada procesador disponible posee el mismo tiempo de ejecuci\\'on, y que los procesos individuales no tienen afinidad con un determinado procesador. Esto es lo que le da una idoneidad a los sistemas integrados.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{Least Laxity First - Condiciones necesarias}\n");
    fprintf(fp,"Este algoritmo de programaci\\'on primero selecciona aquellos procesos que tienen el tiempo de holgura m\\'as peque\\~no. \n"); 
    fprintf(fp,"\\\\El tiempo de holgura se define como la diferencia temporal entre el tiempo l\\'imite, el tiempo de ready y el tiempo de ejecuci\\'on.\n");
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\ M\\'as formalmente, el tiempo de holgura s para un proceso se define como:\n");
    fprintf(fp,"\\\\ \\textit{  s = (d-t)  -c }   \n");
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\ donde d es el tiempo l\\'imite del proceso, t es el tiempo real desde el inicio del ciclo, y c es el tiempo de c\\'alculo restante.\n");
    fprintf(fp,"\\end{frame} \n");

    fprintf(fp,"\\begin{frame}\n");
    fprintf(fp,"\\color{white}\n");
    fprintf(fp,"\\frametitle{Ejecuci\\'on}\n");
    fprintf(fp,"\\resizebox{\\linewidth}{!}{\n"); 
    fprintf(fp,"\\\\RM \n");
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\ \\begin{tabular}{*{30}{1}}\n");
    fprintf(fp,"\\\\ \\toprule  \n");
    fprintf(fp,"Tareas &1&2&3&4&5&6&7&8&9&10&11&12&13&14&15&16&17&18&19&20&21&22&23&24&25&26&27&28\n");
    fprintf(fp,"\\\\ \\midrule  \n");
    fprintf(fp,"Tarea 1& \\cellcolor{blue!25}& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 2& & & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 3& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 4& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 5& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 6& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"\\\\ \\bottomrule  \n");
    fprintf(fp,"\\\\ \\end{tabular}\n");
    fprintf(fp,"\\\\ }\n");

    ///EDF
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\resizebox{\\linewidth}{!}{\n"); 
    fprintf(fp,"\\\\EDF \n");
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\ \\begin{tabular}{*{30}{1}}\n");
    fprintf(fp,"\\\\ \\toprule  \n");
    fprintf(fp,"Tareas &1&2&3&4&5&6&7&8&9&10&11&12&13&14&15&16&17&18&19&20&21&22&23&24&25&26&27&28\n");
    fprintf(fp,"\\\\ \\midrule  \n");
    fprintf(fp,"Tarea 1& &\\cellcolor{blue!25}& & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 2& & & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 3& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 4& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 5& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 6& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"\\\\ \\bottomrule  \n");
    fprintf(fp,"\\\\ \\end{tabular}\n");
    fprintf(fp,"\\\\ }\n");
    ///// LLF
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\resizebox{\\linewidth}{!}{\n"); 
    fprintf(fp,"\\\\LLF \n");
    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\\\ \\begin{tabular}{*{30}{1}}\n");
    fprintf(fp,"\\\\ \\toprule  \n");
    fprintf(fp,"Tareas &1&2&3&4&5&6&7&8&9&10&11&12&13&14&15&16&17&18&19&20&21&22&23&24&25&26&27&28\n");
    fprintf(fp,"\\\\ \\midrule  \n");
    fprintf(fp,"Tarea 1& & & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 2& & &\\cellcolor{blue!25}& & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 3& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 4& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 5& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"Tarea 6& & & & & & & & & & & & & & & & & & & & & & & & & & &  \\\\ \n");
    fprintf(fp,"\\\\ \\bottomrule  \n");
    fprintf(fp,"\\\\ \\end{tabular}\n");
    fprintf(fp,"\\\\ }\n");

    fprintf(fp,"\\newline\n");
    fprintf(fp,"\\end{frame} \n");

    // fprintf(fp,"\\frame{\\frametitle{knapSack}\n ");
    // fprintf(fp,"\\begin{center}\n ");
    // fprintf(fp,"\\begin{tabular}{|");
    // // for ( i = 0; i <= numero; ++i)
    // // {
    // //     fprintf(fp,"l |");
    // // }

    // fprintf(fp,"} \\hline\n");

    
    // // for (i = 0; i <= max; i++) {
    // //     for (j = 1; j <= numero; j++) {
    // //         if (colores[j][i]==0)
    // //         {
    // //             fprintf(fp,"\\color{red}");
    // //         }
    // //         else{
    // //             fprintf(fp,"\\color{green}");
    // //         }
    // //         fprintf(fp,"%d",resultado[j][i]);
    // //         if (j==numero)
    // //         {
    // //             fprintf(fp,"\\\\ \\hline\n");
    // //         }
    // //         else{
    // //             fprintf(fp,"&");
    // //         }
    // //     }
    // // }

    // fprintf(fp,"\\end{tabular}\n");
    // fprintf(fp,"\\end{center}\n ");
    // fprintf(fp,"}\n");
    fprintf(fp,"\\end{document}");
    fclose(fp);
    system("pdflatex schedulingRTOS.tex");
    system("evince --presentation schedulingRTOS.pdf");

}