#include <stdio.h>
#include <curl/curl.h>
#include <string.h>


size_t write_data(char *buffer, size_t size, size_t nmemb, FILE *fp){
	return fwrite(buffer, size, nmemb, fp); 
	}



int curling(void) {
	CURL* handle;
	FILE *fp = fopen("pagetop.html", "wb");

	curl_global_init(CURL_GLOBAL_ALL);


	handle = curl_easy_init();

	if (handle){
		CURLcode success;
		curl_easy_setopt(handle, CURLOPT_URL, "https://www.bay12games.com/dwarves/older_versions.html");
		curl_easy_setopt(handle, CURLOPT_WRITEDATA, fp);
	
		success= curl_easy_perform(handle);
		curl_easy_cleanup(handle);
return 0;
	}	
}

void downloader(char *name){
	char url_download[100];
	snprintf(url_download, sizeof(url_download),"https://www.bay12games.com/dwarves/%s.tar.bz2",name);

	printf("Using URL::%s\n", url_download);
	CURL *curl = curl_easy_init();


	if (curl){
		FILE *fp = fopen("df_new.tar.bz2","wb");
		curl_easy_setopt(curl, CURLOPT_URL, url_download);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);

		curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);

		CURLcode res = curl_easy_perform(curl);

		fclose(fp);

		curl_easy_cleanup(curl);

		if (res!= CURLE_OK){
			fprintf(stderr, "Download FAILED: %s\n", curl_easy_strerror(res));

		}
		else{
		printf("Download SUCCEEDED :>");
		}
	}

	

}

int parsing(void){
	char choice;
	FILE *fp = fopen("pagetop.html","r");
	char buffer[3461];
	size_t ByteRead= fread(buffer,1,3460,fp);

	buffer[ByteRead]='\0';
	printf("---------\n");

	
	char *end = strstr(buffer, ".tar.bz2");
	char *backtrack = (end - 20);
	char *start = strstr(backtrack,"df_");
	int len = end - start;
	char name_new_ver[20];
	strncpy(name_new_ver ,start ,len);
	name_new_ver[len]= '\0';
        
        printf("CURRENT LATEST DF VERSION: %s\n", name_new_ver);
	printf("Start Download[y/n]\n");
	choice = getchar();
	if (choice == 'Y' || choice =='y'){
		printf("Downloading...\n");
		downloader(name_new_ver);
	} else if (choice == 'N' || choice == 'n'){
		return 1;}
	else {
		printf("Invalid input\n");
		return 1;
	}
		

	return 0;
}



int main(void){
	printf("Scraping bay12games site...\n");
	curling();
	printf("Scraped bay12games site and saved to pagetop.html\n");
	parsing();

	return 0;
}

