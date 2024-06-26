#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "fields.h"
#include "dllist.h"
#include "jval.h"
void yazdir(Dllist tmp,Dllist l,char *argv)
{
	FILE *dosya = fopen(argv, "w");

 	while (tmp != l)
	{

		if(strcmp(jval_s(dll_val(tmp)),"\\b")== 0)
		{
			printf("%s", " ");
			fprintf(dosya, " ");
		}
		else if(strcmp(jval_s(dll_val(tmp)),"\\n")== 0)
		{
		
			printf("\n");
			fprintf(dosya, "\n");
		}
		else
		{
			printf("%s", tmp->val.s);
			fprintf(dosya, "%s", tmp->val.s);
		}
		tmp = tmp->flink;
	}

	printf("\n");
	fclose(dosya);
}

Dllist yaz(Dllist gec,int sayi,int i,IS is,Dllist l)
{	
	for(int j=0;j<sayi;j++)
    	{
   		dll_insert_a(gec, new_jval_s(strdup(is->fields[i])));
    		gec=gec->flink;
    	}
    	if(gec==l)
    		return gec->blink;
    	else 
    		return gec;
}

Dllist sil(Dllist gec, int sayi, int i, IS is,Dllist l) {
    int silinecek = 0; // Silinen düğüm sayısını izlemek için bir sayaç
    while (gec != l && silinecek < sayi) {
        if (strcmp(jval_s(dll_val(gec)), is->fields[i]) == 0) 
        {
            Dllist sil = gec;
            gec = gec->blink; 
            dll_delete_node(sil);
            silinecek++; // Silinen sayısını artır
        } else 
        {
            gec = gec->blink; 
        }
    }
    return gec;
}



int main(int argc, char **argv)
{
  IS is;
  int i;
  Dllist l, tmp,gec;
  l = new_dllist();
  gec=l;

    if (argc != 3) 
  { 
  	fprintf(stderr, "3 adet argüman girmelisiniz. Örn= ./programAdi(main) okunacakDosyaAdi yazilacakDosyaAdi \n"); exit(1);
  }
 int uzunluk = strlen(argv[1]);
 if(uzunluk >= 4 && strcmp(argv[1] + uzunluk - 4, ".dat") == 0)//.dat uzantiliysa gir
 {
 if (strcmp(argv[1], "giris.dat") != 0)//giris.dat degilse hata ver
 {
 	printf("okunacakDosyaAdi kismini giris.dat olarak girmeniz gerekmektedir.\n");
 }
}
else
{
printf(".dat uzantili bir dosya kullanin.\n");exit(1);
}

if(strcmp(argv[2], "cikis.dat") != 0)
{
 printf("yazilacakDosyaAdi kismini cikis.dat olarak girmeniz gerekmektedir.\n");
}


  /* Open the file as an inputstruct.  Error check. */

  is = new_inputstruct(argv[1]);
  if (is == NULL) {
    perror(argv[1]);
    exit(1);
  }

while(get_line(is) >= 0) 
{
	i=0;
	
   if(strcmp(is->fields[i],"yaz:")==0)  //ikisi birbirine esitse strcmp fonksiyonu 0 dondurur
    { 
    
    	for ( i = 1; i < is->NF; i++) //Satirdaki verileri tek tek okur.
    	{
    		int sayi;
    		sayi=atoi(is->fields[i]);
    		i++; //harf'e gecsin diye indisi artirdim
    		gec=yaz(gec,sayi,i,is,l);
    	}
    }
 
    
    else if(strcmp(is->fields[i],"sil:")==0)  //ikisi birbirine esitse strcmp fonksiyonu 0 dondurur
    {
    //bulundugu konumdan geriye dogru giderek girilen adet kadar basa dogru siler
    	for ( i = 1; i < is->NF; i++) //Satirdaki verileri tek tek okur.
    	{
    		int sayi;
    		sayi=atoi(is->fields[i]);
    		i++;
    		gec=sil(gec,sayi,i,is,l);
    	}
    }

    
    else if(strcmp(is->fields[i],"sonagit:")==0)  //ikisi birbirine esitse strcmp fonksiyonu 0 dondurur
    {
      gec=dll_last(l);
    }
     
    else //dur: okundugunda bu islemler yapilacak
    {
    //dosyaya yazdirma islemi yapilacak
    //dosyaya yazarken bagli listedeki value'da \b varsa dosyaya bosluk olarak \n yaziyorsa 
    //alt satira giderek yazdirilacak
    	
    	
    	//Ekrana yazdirma kismi burasi. Kontrol amacli yazilmisti
    	tmp = l->flink;
	yazdir(tmp,l,argv[2]);
    	return 0;
    }
   

    
}

  jettison_inputstruct(is);
  return 0;

}

