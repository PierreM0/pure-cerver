#define STDOUT 1
#define STDERR 1
#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1


typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef unsigned int size_t;
typedef unsigned int socklen_t;
typedef int ssize_t;

#define AF_INET 2
#define SOCK_STREAM 1
#define IPPROTO_TCP 0
#define INADDR_ANY 0

typedef struct {
  uint16_t sin_family; /* 2 */
  uint16_t sin_port;   /* 4 network order */
  uint32_t sin_addr;   /* 8 */
  char sin_zero[8];    /* 16 */
} sockaddr_in_t;


int write(int fd, void* buf, int buflen);
int close(int fd);
int socket(int domain, int type, int protocol);
int accept(int sockfd, void* addr, int* addrlen);
int bind(int sockfd, void* addr, int addrlen);
int listen(int sockfd, int backlog);
int exit(int code);

#define err_log(x) do {write(STDERR, "ERROR: "x, strlen(x) + 7); exit(EXIT_FAILURE); } while(0);
#define info_log(x) write(STDOUT, "INFO: "x, strlen(x) + 6) 


int strlen(const char* str) {
  int i = 0;
  for (; str[i]; ++i);
  return i;
}

int strcat(char* DEST, char* SRC) {
  int dest_len = strlen(DEST);
  int src_len = strlen(SRC);
  int i = dest_len;
    for (; i < src_len + dest_len; ++i) {
    DEST[i] = SRC[i-dest_len];
  }
  return i;
}



int main(int argc, char* argv[]) {
  int i = 0;
  int sockfd;
  int confd;
  sockaddr_in_t addr;

  for (; i < argc; ++i) {
    write(STDOUT, argv[i], strlen(argv[i]));
    write(1, "\n", 1);
  }

  info_log("Creating socket...\n");
  if ((sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) < 0) {
	err_log("socket\n");
  }
  #define EXIT_SUCCESS 0


  info_log("Binding socket...\n");
  addr.sin_family = AF_INET;
  addr.sin_port = 14619; /* 6969 TODO: make a function */ 
  addr.sin_addr = INADDR_ANY;

  if (bind(sockfd, &addr, sizeof(addr)) < 0) {
      err_log("bind");
  }

  info_log("Listening socket...\n");
  if (listen(sockfd, 5) < 0) {
      err_log("listen");
  }

  for(;;) {
    int addr_out_len; sockaddr_in_t SA;
    info_log("Accepting client...\n");
    confd = accept(sockfd, &SA, &addr_out_len);
    (void ) addr_out_len;
    (void ) SA;
    if ( confd < 0 ) err_log("accept\n");

    char html[] = "HTTP/1.1 200 OK\r\n"
       		"Content-Type: text/html; charset=utf-8\r\n"
       		"\r\n"
  		"<h1>test</h1>\r\n";
    write(confd, html, strlen(html));
    close(confd);
  } 
  return EXIT_SUCCESS;
}



