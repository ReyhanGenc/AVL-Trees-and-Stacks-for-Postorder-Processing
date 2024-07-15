#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <windows.h> 
#include "agac.hpp"
#include "yigit.hpp"

using namespace std;

int main() 
{
	ifstream dosya;
	dosya.open("Veri.txt");
	if(!dosya.is_open())
		cout<<"dosya acilamadi"<<endl;
	
	string ilkSatir;
	int satirSayisi=0;
	
	//Dizilerin boyutunu belirlemek için satır sayısı hesaplanır.
	while (getline(dosya, ilkSatir)) 
		satirSayisi++;
    
	dosya.close();
	
	ifstream yenidosya;
	yenidosya.open("Veri.txt");
	
	if(!yenidosya.is_open())
		cout<<"dosya acilamadi"<<endl;
	
	agac *agacDizi= new agac[satirSayisi];
	yigit *yigitDizi = new yigit[satirSayisi];
	
	string satir;
	string yenikelime;
	int index=0;
	
	while (getline(yenidosya, satir)) 
	{
		istringstream satirOku(satir);
		agac *satirAgac= new agac();
		
		// Satır içindeki kelimeleri ayırma işlemi
        while (satirOku >> yenikelime) 
		{
			int sayi=stoi(yenikelime);
			satirAgac->Add(sayi);
        }
		agacDizi[index] = *satirAgac;
		index++;
    }
	
	//yapraklar önce bir yığıta ekleniyor, ardından bu yığıtlar yığıt türünden bir diziye eleman olarak atanıyor.
	for (int i=0; i<satirSayisi; i++)
	{
		yigit *yedekYigit=new yigit();
		agacDizi[i].yaprakmi(yedekYigit);
		yigitDizi[i]=*yedekYigit;
	}
	
	int ebIndex,ekIndex=0;
	int ek,eb;
		
	//En küçük veya en büyük elemanı silmek için gerekli koşula yönlendirmede kullanıldı.
	int silinecek=1;
		
	//en küçük ve en büyük elemanların başlangıç değerleri (index olarak kullanılacak)
	int baslangic=0;
		
	//agac sayısının bir eksiği kadar döngüyü döndürmek için.
	int donguSonlandir;
	
	yigit *yedekYigitDizi= new yigit[satirSayisi];
		
	for(int i=0;i<satirSayisi;i++)
	{
		yigitDugum*	tekrar = yigitDizi[i].topOfStack;
		yigit geciciYigit;
					
		// yigitDizisi'ndeki elemanları geciciYigit'e ters sırayla kopyalanıyor.
		while (tekrar != NULL) 
		{
			geciciYigit.push(tekrar->item); 
			tekrar = tekrar->next; 
		}
					
		// geciciYigit'taki elemanlar ters sırada kopyalandığı için bir kez daha kopyalanıyor.
		while (!geciciYigit.isEmpty()) 
		{
			yedekYigitDizi[i].push(geciciYigit.top());
			geciciYigit.pop(); // En üstteki eleman çıkarıldı.
		}
		delete tekrar;
	}
	
	system("CLS");
	
	// Ağaç dizisinin boyutunun bir eksiği kadar döndürülür, geriye kalan eleman ekrana veri yazdırmak içindir.
	for (int j=1; j<satirSayisi; j++)
	{
		// Ağaç dizisindeki elemanların ascii karşılıkları yazdırılır.
		for (int i=0; i<satirSayisi;i++)
		{
			if(agacDizi[i].root!=NULL)
			{	
				int ascii = agacDizi[i].AVLToplamDugumDeger%(90-65 + 1) + 65;
				cout<<char(ascii);
			}	
		}
			
		for(int i=0;i<satirSayisi;i++)
		{	
			// Yapılan işlemler sonucunda yedek dizideki boşalan elemanı asıl diziden de boşaltırız.
			if(yedekYigitDizi[i].isEmpty())
				yigitDizi[i].makeEmpty();
				
			// Yığıt tamamen boşalmadıysa baştaki haline dönmesi için asıl diziden elemanlar alınır.
			else
			{
				//Diğer elemanlar yukarıda yapıldığı gibi tekrar kopyalanır.
				yigitDugum* tekrar = yigitDizi[i].topOfStack;
				yigit geciciYigit;
			
				yedekYigitDizi[i].makeEmpty();
					
				while (tekrar != NULL) 
				{
					geciciYigit.push(tekrar->item); 
					tekrar = tekrar->next; 
				}
				while (!geciciYigit.isEmpty()) 
				{
					yedekYigitDizi[i].push(geciciYigit.top());
					geciciYigit.pop(); 
				}
				delete tekrar;
			}	
		}
			
		donguSonlandir=1;
		while(donguSonlandir)
		{
			// Başlangıç değeri index olarak kullanılacağı için boş bir yığıta ait index olmamalı
			while(yigitDizi[baslangic].isEmpty())
				baslangic++;
			
			ekIndex=baslangic; ebIndex=baslangic;
			ek=yedekYigitDizi[baslangic].top();
			eb=yedekYigitDizi[baslangic].top();
		
			if (silinecek==1) //en küçük eleman silinir.
			{
				for (int i=1; i<satirSayisi; i++) 
				{
					//Boş olmayan elemanlardan en küçüğü bulunur.
					if(!yedekYigitDizi[i].isEmpty()){
						if(yedekYigitDizi[i].top()<ek)
						{
							ekIndex=i;
							ek=yedekYigitDizi[i].top();
						}					
					}
				}
				yedekYigitDizi[ekIndex].pop();
				
				// yığıt boşalmadıysa en büyük eleman aramasına yönlendiriliyor.
				if(!yedekYigitDizi[ekIndex].isEmpty())
					silinecek=0;
					
				// yığıt boşaldıysa agacDizi'de eşleşen indexli agac siliniyor.
				else 
				{
					agacDizi[ekIndex].Clear();
					donguSonlandir=0;
				}
			}
	
			if (silinecek==0) //en büyük eleman silinir.
			{
				for (int i=1; i<satirSayisi; i++) 
				{
					if(!yedekYigitDizi[i].isEmpty())
					{
						if(yedekYigitDizi[i].top()>eb)
						{
							ebIndex=i;
							eb=yedekYigitDizi[i].top();
						}
					}							
				}
				yedekYigitDizi[ebIndex].pop();
				
				// Yığıt boşalmadıysa en küçük elemanın çıkarılması için sayaca değer atanır.
				if(!yedekYigitDizi[ebIndex].isEmpty())
					silinecek=1;
					
				else 
				{
					agacDizi[ebIndex].Clear();
					donguSonlandir=0;
				}
			}
		}			
		Sleep(3);
		system("CLS");
	}
	
	//döngü ile kalan son elemanın indexi hesaplanıyor.
	int kalanEleman=0;
	while(agacDizi[kalanEleman].isEmpty())
				kalanEleman++;
	
	cout<<"=============================="<<endl;
	cout<<"|                            |"<<endl;
	cout<<"|                            |"<<endl;
		
	int ascii = agacDizi[kalanEleman].AVLToplamDugumDeger%(90-65 + 1) + 65;
	cout<<"|     Son Karakter: "<<char(ascii)<<"        |"<<endl;
		
	cout<<"|     AVL No      : "<<kalanEleman+1<<"      |"<<endl;
		
	cout<<"|                            |"<<endl;
	cout<<"|                            |"<<endl;
	cout<<"=============================="<<endl;
		
	yenidosya.close();
	delete [] agacDizi;
	delete [] yigitDizi;
	delete [] yedekYigitDizi;
	return 0;
}