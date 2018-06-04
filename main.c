#include <gtk/gtk.h>
#include "beamer.h"
// #include "logicInterfaz.h"

#define bufSize 1024

GtkBuilder *gtkBuilder;
GtkWidget *window;
GtkWidget *btn_cancelar;
GtkWidget *btn_procesar;
GtkWidget *btn_create;
GtkWidget ***tasks;
GtkWidget ***threadsInterfaz;
GtkWidget *spn_numProcess;
GtkWidget *SRWindowThreads;
GtkWidget *scrWndNtasks;
GtkWidget *scrWndTasksErrors;
GtkWidget **objetos;


GtkWidget * radbtn_rm_si;
GtkWidget * radbtn_rm_no;
GtkWidget * radbtn_edf_si;
GtkWidget * radbtn_edf_no;
GtkWidget * radbtn_llf_si;
GtkWidget * radbtn_llf_no;

GtkWidget * chckBtn_rm;
GtkWidget * chckBtn_edf;
GtkWidget * chckBtn_llf;


char *filename;
int nObjetos;
char **infoThreads;

void on_window_destroy (GtkWidget *object, gpointer user_data) {
    gtk_main_quit();
}


void processThreads(){
	printf("Inside processThreads\n");
	int runRM = 0;
	int runEDF = 0;
	int runLLF = 0;

	int aloneRM = 0;
	int aloneEDF = 0;
	int aloneLLF = 0;
	
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chckBtn_rm))){
		runRM = 1;
		printf(" chckBtn_rm\n");
	} 
	if(runRM){
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radbtn_rm_si))){
			aloneRM = 1;
			printf(" Slide Alone for RM\n");
		} 
	}
	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chckBtn_edf))){
		runEDF = 0;
		printf("chckBtn_edf\n");
	}
	if(runEDF){
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radbtn_edf_si))){
			aloneEDF = 1;
			printf(" Slide Alone for EDF\n");
		} 
	}

	if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(chckBtn_llf))){
		runLLF = 0;
		printf("chckBtn_llf\n");
	}
	if(runLLF){
		if (gtk_toggle_button_get_active(GTK_TOGGLE_BUTTON(radbtn_llf_si))){
			aloneLLF = 1;
			printf(" Slide Alone for LLF\n");
		} 
	}


	printf("nTasks %d\n", nObjetos );

	int* nPeriods;
	int* nComputations;

	// int nt=0;
	// int nw=0;
	
	nPeriods = (int*) calloc(nObjetos,sizeof(int *));
	nComputations = calloc(nObjetos,sizeof(int*));
	// for (int i=0;i<nObjetos;i++){
	// 	info[i] = calloc(nObjetos+1,sizeof(int));
	// }
	GList *children, *iter;
	children = gtk_container_get_children(GTK_CONTAINER(scrWndTasksErrors));
	for(iter = children; iter != NULL; iter = g_list_next(iter))
	  gtk_widget_destroy(GTK_WIDGET(iter->data));
	g_list_free(children);

	int y;
	int x;
	int valor;
	int valor2;
	GtkWidget *table;
	table = gtk_grid_new();
	gtk_container_add (GTK_CONTAINER (scrWndTasksErrors), table);
	int continueB = 1;

	 for(y=0; y<nObjetos;y++){ //filas
	 	printf("Estoy en el for.\n");
	 	valor = atoi(gtk_entry_get_text(GTK_ENTRY(tasks[y][1])));
	 	nPeriods[y] = valor;
	 	printf("> %d ", nPeriods[y] );
	 	valor2 = atoi(gtk_entry_get_text(GTK_ENTRY(tasks[y][2])));
	 	nComputations[y] = valor2;
	 	printf("> %d \n", nComputations[y]);	
	 	if(nPeriods[y]<nComputations[y]){
	 		GtkWidget *label;
	 		continueB = 0;
	 		char str[2000];
			sprintf(str, "** Verifique la tarea %d, tiene el tiempo de ejecución mayor al periodo.  ", y);					
            label=gtk_label_new(str);
            gtk_grid_attach (GTK_GRID (table), label, 0, y, 1, 1);
	 		
	 	} 	
	   }
	 gtk_widget_show_all (window);  
	 printf("continueB %d\n", continueB );
	 if(continueB == 1){
	 	printf("Inside continueB ==1  %d\n", continueB );
	 	schedulingRTOSBeamer(nObjetos, runRM,aloneRM,runEDF,aloneEDF,runLLF,aloneLLF,nPeriods,nComputations);
	 }
	//}
	// //starProcessLottery(isExp,  numThreadsUI, quantum,nWork,nTickets,names);
}
// void hola(){
// 	printf("KArhy\n");
// }

// void preparedAlgorithms(int nTasks, int runRM, int aloneRM, int runEDF, int aloneEDF, int runLLF, int aloneLLF, int* nPeriods, int* nComputations){
// 	printf("Inside preparedAlgorithms");
// 	typedef struct t Table;
// 	typedef struct g Game;
// 	typedef struct lcm LeastCommon;
// 	printf("Inside preparedAlgorithms");
// 	Table* table;
// 	table = calloc(nTasks, sizeof(Table));
// 	int** ejecutionTable;
// 	int cont = 0;
// 	for(cont=0; cont<nTasks;cont++){ 
// 		strcpy(table[cont].task,"1");
// 		table[cont].ejecutionTime= nComputations[cont];
// 		table[cont].period= nPeriods[cont];
// 		table[cont].isActive=1;
// 		table[cont].stillRunning=0;
// 		table[cont].times=1;
// 		table[cont].remaining=0;

// 		printf("table[cont].ejecutionTime: %d", table[cont].ejecutionTime);
// 		printf("table[cont].period: %d", table[cont].period);
// 	}
// }//preparedAlgorithms
void generaTasksInfo(GtkWidget *widget, gpointer user_data)
{
	GList *children, *iter;

	children = gtk_container_get_children(GTK_CONTAINER(SRWindowThreads));
	for(iter = children; iter != NULL; iter = g_list_next(iter))
	  gtk_widget_destroy(GTK_WIDGET(iter->data));
	g_list_free(children);

	children = gtk_container_get_children(GTK_CONTAINER(scrWndNtasks));
	for(iter = children; iter != NULL; iter = g_list_next(iter))
	  gtk_widget_destroy(GTK_WIDGET(iter->data));
	g_list_free(children);
	GtkWidget *table;

    printf(" Inside generaTasksInfo\n");
    gint cantObjs = gtk_spin_button_get_value_as_int (spn_numProcess);
    nObjetos = cantObjs;

    if(nObjetos == 0 || nObjetos<0 || nObjetos>7){
	    GtkWidget *table;
		table = gtk_grid_new();
		gtk_container_add (GTK_CONTAINER (scrWndNtasks), table);
		GtkWidget *label;
 		char str[2000];
		sprintf(str, "** El numero de tareas debe estar en el rango de 0 a 1.");					
        label=gtk_label_new(str);
        gtk_grid_attach (GTK_GRID (table), label, 0, 0, 1, 1);
    }else{
    	printf(" nTasks:  %d\n",nObjetos );
	    
	    table = gtk_grid_new();
	    tasks= calloc(nObjetos+1,sizeof(GtkWidget));
	    int i;
	    for(i=0; i<nObjetos+1;i++)
	        tasks[i]=calloc(nObjetos,sizeof(GtkWidget));
	    gtk_container_add (GTK_CONTAINER (SRWindowThreads), table);

	    int x;
	    int y;
	    for(x=0;x<3;x++){ //columnas
	       for(y=0; y<nObjetos+1;y++){ //filas
	            GtkWidget *label;
	            if(y==0){
	            	if(x==0){            		
	                    label=gtk_label_new(" ");
	                }else if(x==1){
	                    label=gtk_label_new("Periodo ");
	                }else if(x==2){
	                    label=gtk_label_new("Tiempo de ejecucion ");
	                }                
	                gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);
	            }else{            	
	          		if(x == 0){          			
	          			char str[20];
						sprintf(str, "Tarea %d:  ", y);					
	                    label=gtk_label_new(str);
	                    gtk_grid_attach (GTK_GRID (table), label, x, y, 1, 1);
	          		}else{
	          			GtkWidget *entry;
		                entry = gtk_entry_new ();
		                tasks[y-1][x]= entry; 
		                gtk_grid_attach (GTK_GRID (table), entry, x, y, 1, 1); 	                

	          		}                   

	                   
	            }       
	        }// end primer for
	    }//end for  
    }
	    
    gtk_widget_show_all (window);  
}

int main(int argc, char *argv[])
{
   
    gtk_init(&argc, &argv);
    
    gtkBuilder = gtk_builder_new();
    gtk_builder_add_from_file(gtkBuilder, "Interfaz.glade", NULL);
    window = GTK_WIDGET(gtk_builder_get_object(gtkBuilder, "Interfaz"));
    gtk_window_set_default_size(GTK_WINDOW(window), 800, 700);

    btn_cancelar = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btn_cancelar"));
    btn_procesar = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btn_procesar"));
    btn_create =  GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "btn_create"));
    spn_numProcess = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "spn_numProcess"));
    
    SRWindowThreads = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "SRWindowThreads"));
    gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(SRWindowThreads),600);
    scrWndTasksErrors =  GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "scrWndTasksErrors"));
    gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrWndTasksErrors),600);
    scrWndNtasks=  GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "scrWndNtasks"));
     gtk_scrolled_window_set_min_content_width(GTK_SCROLLED_WINDOW(scrWndNtasks),200);
    radbtn_rm_si = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "radbtn_rm_si"));
    radbtn_rm_no = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "radbtn_rm_no"));

    radbtn_edf_si = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "radbtn_edf_si"));
    radbtn_edf_no = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "radbtn_edf_no"));

    radbtn_llf_si = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "radbtn_llf_si"));
    radbtn_llf_no = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "radbtn_llf_no"));

    chckBtn_rm = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "chckBtn_rm"));
    chckBtn_edf = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "chckBtn_edf"));
    chckBtn_llf = GTK_WIDGET (gtk_builder_get_object (gtkBuilder, "chckBtn_llf"));

    g_signal_connect (window, "destroy", G_CALLBACK (on_window_destroy), NULL);
    g_signal_connect (btn_cancelar, "clicked", G_CALLBACK (on_window_destroy), NULL);
    g_signal_connect (btn_create, "clicked",G_CALLBACK (generaTasksInfo),NULL);
    g_signal_connect (btn_procesar, "clicked",G_CALLBACK (processThreads),NULL);
    

    gtk_widget_set_tooltip_text (btn_procesar, "Inicia la ejecución de las tareas. ");  
   	//itemSalir
    g_object_unref(G_OBJECT(gtkBuilder));
    gtk_widget_show(window);
    gtk_main();
    
    return 0;
}