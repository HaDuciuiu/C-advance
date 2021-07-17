#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <cjson/cJSON.h>
 
#include <curl/curl.h>
 
struct MemoryStruct {
  char *memory;
  size_t size;
};
 
static size_t
WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct MemoryStruct *mem = (struct MemoryStruct *)userp;
 
  char *ptr = realloc(mem->memory, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->memory = ptr;
  memcpy(&(mem->memory[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->memory[mem->size] = 0;
 
  return realsize;
}
 
int main(void)
{
  CURL *curl_handle;
  CURLcode res;
  cJSON *json;
 
  struct MemoryStruct chunk;
 
  chunk.memory = malloc(1);  /* will be grown as needed by the realloc above */
  chunk.size = 0;    /* no data at this point */
 
  curl_global_init(CURL_GLOBAL_ALL);
 
  /* init the curl session */
  curl_handle = curl_easy_init();
 
  /* specify URL to get */
  curl_easy_setopt(curl_handle, CURLOPT_URL, "https://official-joke-api.appspot.com/jokes/programming/random");
 
  /* send all data to this function  */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
  /* we pass our 'chunk' struct to the callback function */
  curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)&chunk);
 
  /* some servers don't like requests that are made without a user-agent
     field, so we provide one */
  curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
 
  /* get it! */
  res = curl_easy_perform(curl_handle);
 
  /* check for errors */
  if(res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }
  else {
    /*
     * Now, our chunk.memory points to a memory block that is chunk.size
     * bytes big and contains the remote file.
     *
     * Do something nice with it!
     */
 
    printf("%lu bytes retrieved\n", (unsigned long)chunk.size);


    json = cJSON_Parse(chunk.memory);

    cJSON *tmp;

    cJSON_ArrayForEach(tmp, json){
      cJSON *id = cJSON_GetObjectItemCaseSensitive(tmp, "id");
      cJSON *type = cJSON_GetObjectItemCaseSensitive(tmp, "type");
      cJSON *setup = cJSON_GetObjectItemCaseSensitive(tmp, "setup");
      cJSON *punchline = cJSON_GetObjectItemCaseSensitive(tmp, "punchline");

      if(cJSON_IsNumber(id) && cJSON_IsString(type) && cJSON_IsString(setup) && cJSON_IsString(punchline)){
        printf("id: %d, type: %s, setup: %s, punchline: %s\n", id->valueint, type->valuestring, setup->valuestring, punchline->valuestring);
      }
    }
  }
  cJSON_Delete(json);
  /* cleanup curl stuff */
  curl_easy_cleanup(curl_handle);
 
  free(chunk.memory);
 
  /* we're done with libcurl, so clean it up */
  curl_global_cleanup();
 
  return 0;
}

// #include <curl/curl.h> 
// #include <stdio.h> 


// int main(){ 
// CURL *image; 
// CURLcode imgresult; 
// FILE *fp; 

// image = curl_easy_init(); 
// if( image ){ 
//     // Open file 
//     fp = fopen("google.jpg", "wb"); 
//     if( fp == NULL ) printf("File cant open!\n");

//     curl_easy_setopt(image, CURLOPT_URL, "https://upload.wikimedia.org/wikipedia/commons/thumb/f/fe/Son_Tung_M-TP_1_\%282017\%29.png/404px-Son_Tung_M-TP_1_\%282017\%29.png"); 
//     curl_easy_setopt(image, CURLOPT_WRITEFUNCTION, NULL); 
//     curl_easy_setopt(image, CURLOPT_WRITEDATA, fp); 


//     // Grab image 
//     imgresult = curl_easy_perform(image); 
//     if( imgresult ){ 
//         printf("Cannot grab the image!\n"); 
//     } 
// } 

// // Clean up the resources 
// curl_easy_cleanup(image); 
// // Close the file 
// fclose(fp); 
// return 0; 
// } 