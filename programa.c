num				[0-9]
letra_num		[a-z.A-Z.á-ź.Á-Ź.0-9]
marca			("Xiaomi"|"ONEPLUS"|"Ulefone"|"Alcatel"|"Nokia"|"Iphone"|"Oppo")
medida_bateria	("mAh"|"Miliamperios")
bateria			({num}*"."?","?{num}+" "?{medida_bateria}{1})
posibles_so		("MIUI"|"Android"|"IOS"|"OxygenOS")
SO				({posibles_so}{1}" "?{letra_num}+)
medida_memoria 	["GB"|"MB"|"TB"]
memoria 		({num}+" "?{medida_memoria}{2})
movil 			("Móvil "{num}+)
encontrar_ram	("RAM"\n)
pulgadas		({letra_num}+"."?" "?","?{letra_num}+?"Pulgadas")
tipo_modelo		("Redmi"|"Nord"|"Ulefone armor"|"Xiaomi MI"|"Oppo Find"|"Samsung Galxy"|"Redmi Note")
modelo 			({tipo_modelo}" "?{letra_num}+)
peso			({num}{3,4}" gramos")
usb_es_en		("USB Type C"|"USB tipo C")
encontrar_alm	("Capacidad de almacenamiento de memoria\n"|"Capacidad de la memoria\n")
tecnologia_red	("3G"|"4G"|"5G")
red 			({tecnologia_red}"\n")
%{
	int misma_bateria=0,misma_marca=0,mismo_so = 0,encontrada_ram=0,misma_ram=0,misma_pulgada=0,mismo_modelo=0,mismo_peso=0,encontrado_alm=0,mismo_alm=0,misma_red=0;
%}
%%
{movil}		{printf("\n\nEncontrado %s ",yytext);
				misma_bateria=0;
				misma_marca=0;
				mismo_so=0;
				encontrada_ram=0;
				misma_ram=0;
				misma_pulgada=0;
				mismo_modelo=0;
				mismo_peso=0;
				encontrado_alm=0;
				mismo_alm=0;
				misma_red=0;
			}
{marca}		{if(!misma_marca) printf("\tMarca %s \n",yytext);misma_marca=1;}
{bateria}	{if(!misma_bateria) printf("\tBateria de %s \n",yytext);misma_bateria=1;}
{SO}		{if(!mismo_so)printf("\tSistema operativo %s \n",yytext);mismo_so=1;}
{encontrar_ram}	{if(!misma_ram && !encontrada_ram)encontrada_ram=1;}
{encontrar_alm}	{if(!mismo_alm && !encontrado_alm)encontrado_alm=1;}
{memoria}	{if(encontrada_ram){
				misma_ram=1;
				encontrada_ram=0;
				printf("\tRAM de %s \n",yytext);
				}
			 if(encontrado_alm){
			 	mismo_alm=1;
			 	encontrado_alm=0;
			 	printf("\tAlmacenamiento de %s \n",yytext);
			 }
			}
{pulgadas}	{if(!misma_pulgada)printf("\tTamaño de %s \n",yytext);misma_pulgada=1;}
{modelo}	{if(!mismo_modelo)printf("modelo %s \n",yytext);mismo_modelo=1;}
{peso}		{if(!mismo_peso)printf("\tPeso %s \n",yytext);mismo_peso=1;}
{usb_es_en}	{printf("\tUSB tipo C\n");}
{red}		{if(!misma_red)printf("\tTecnología red %s",yytext);misma_red=1;}
.|\n 		{;}
%%
int yywrap(){
	return 1;
}
int main(){
	yylex();
	return 1;
}
