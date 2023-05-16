#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<string.h>

typedef struct strbuf {
  int len;     //当前缓冲区（字符串）长度
  int alloc;   //当前缓冲区（字符串）容量
  char *buf;   //缓冲区（字符串）
}STRB;

void strbuf_init(struct strbuf *sb, size_t alloc); 	//初始化 sb 结构体，容量为 alloc。
void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc); //	将字符串填充到 sb 中，长度为 len, 容量为 alloc。
void strbuf_release(struct strbuf *sb); 	//释放 sb 结构体的内存。
void strbuf_swap(struct strbuf *a, struct strbuf *b);// 	交换两个 strbuf。
char *strbuf_detach(struct strbuf *sb, size_t *sz); //	将 sb 中的原始内存取出，并将 sz 设置为其 alloc 大小 。
int strbuf_cmp(const struct strbuf *first, const struct strbuf *second);// 	比较两个 strbuf 的内存是否相同。
void strbuf_reset(struct strbuf *sb); 	//清空 sb。

void strbuf_init(struct strbuf *sb,size_t alloc){
sb=(STRB *)malloc(sizeof(STRB));
sb->alloc=alloc;
}

void strbuf_attach(struct strbuf *sb, void *str, size_t len, size_t alloc){
    sb->buf=(char *)malloc(sizeof(char)*sb->alloc);
    memcpy(sb->buf,str,len);
    sb->alloc=alloc;
    sb->len=len;
}

void strbuf_release(struct strbuf *sb){
    free(sb->buf);
    sb->buf=NULL;
    //free(sb);
}

void strbuf_swap(struct strbuf *a, struct strbuf *b){
    STRB *c;
    c=a;
    a=b;
    b=c;
}

char *strbuf_detach(struct strbuf *sb, size_t *sz){
*sz=sb->alloc;
return sb->buf;
}

int strbuf_cmp(const struct strbuf *first, const struct strbuf *second){
    if(first->buf==second->buf){
        return 1;
    }
    return 0;
}

void strbuf_reset(struct strbuf *sb){
    sb->alloc=0;
    sb->len=0;
    sb->buf=NULL;
}

void strbuf_grow(struct strbuf *sb, size_t extra);//	确保在 len 之后 strbuf 中至少有 extra 个字节的空闲空间可用。
void strbuf_add(struct strbuf *sb, const void *data, size_t len); //	向 sb 追加长度为 len 的数据 data。
void strbuf_addch(struct strbuf *sb, int c);// 	向 sb 追加一个字符 c。
void strbuf_addstr(struct strbuf *sb, const char *s);// 	向 sb 追加一个字符串 s。
void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2);// 	向一个 sb 追加另一个 strbuf的数据。
void strbuf_setlen(struct strbuf *sb, size_t len); 	//设置 sb 的长度 len。
size_t strbuf_avail(const struct strbuf *sb) ;	//计算 sb 目前仍可以向后追加的字符串长度。
void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len);// 	向 sb 内存坐标为 pos 位置插入长度为 len 的数据 data。
//追加覆盖末尾\0

void strbuf_grow(struct strbuf *sb, size_t extra){
    if(extra>=sb->alloc-sb->len)
    exit(-1);
}

void strbuf_add(struct strbuf *sb, const void *data, size_t len){
    //sb->len+=len;
    memcpy(sb->buf+sb->len,data,len);
}

void strbuf_addch(struct strbuf *sb, int c){
    char a[2]={0};
    a[0]=c;
    memcpy(sb->buf,a,2);
    //sb->len++;
}

void strbuf_addstr(struct strbuf *sb, const char *s){
    memcpy(sb->buf+sb->len,s,strlen(s)+1); 
    //sb->len+=strlen(s);
}

void strbuf_addbuf(struct strbuf *sb, const struct strbuf *sb2){
    //sb->len+=sb2->len;
    memcpy(sb->buf+sb->len,sb2->buf,sb->len);
}

void strbuf_setlen(struct strbuf *sb, size_t len){
    sb->len=len;
}

size_t strbuf_avail(const struct strbuf *sb) {
    return sb->alloc-sb->len;
}

void strbuf_insert(struct strbuf *sb, size_t pos, const void *data, size_t len){
    char *a=sb->buf+pos;
    memcpy(sb->buf+pos,data,len);
    memcpy(sb->buf+pos+len,a,strlen(a)+1);
}






int main() {
  struct strbuf sb;
  strbuf_init(&sb, 10);
  strbuf_attach(&sb, "xiyou", 5, 10);
  assert(strcmp(sb.buf, "xiyou") == 0);
  strbuf_addstr(&sb, "linux");
  assert(strcmp(sb.buf, "xiyoulinux") == 0);
  strbuf_release(&sb);
}