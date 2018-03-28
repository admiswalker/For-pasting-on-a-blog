#include "socket.hpp"


bool sstd::sockSSL::open(){
	struct addrinfo addressinfo;				//配列として用意される訳では無いので、freeaddrinfo(addressinfo);の必要は無い。
	
	//addressinfo.ai_flags    = AI_PASSIVE;	//これを指定すると accept(2) するためのソケットを bind(2) するのに適したものとなる。通常サーバ側のプログラムで用いられる。
														//今回はクライアント側なので、コメントアウト。
	
	addressinfo.ai_flags    = 0;				//addressinfo.ai_flags に AI_PASSIVE フラグがセットされていない場合、 返されるソケットアドレスは connect(2), sendto(2), sendmsg(2) での使用に適したものとなる。
	addressinfo.ai_family   = AF_UNSPEC;		//getaddrinfo()にIPv4かIPv6のアドレスのバイナリ値??を変えさせる。
	addressinfo.ai_socktype = SOCK_STREAM;		//トランスポート層??の設定。
														//SOCK_STREAM:恐らくTCP接続の事。
														//SOCK_DGRAM :恐らくUDP
														//他にもいくつか指定できる。詳細は、「$ man socket」に譲る。
	addressinfo.ai_protocol = 0;				//ネットワーク層??の設定。
														//0:getaddrinfo()が任意のプロトコルのソケットアドレスを返す事を許可する。
														//httpsでアクセスする場合など、SSL/TLSなど任意のプロトコルを許可する……みたいなかんじかな?
														//
														//恐らく、IPv4やIPv6などのいずれか。
	
	struct addrinfo *addressinfo_result;	//addressinfoと同一にしても問題無い??→アドレスで指定されていると言う事は、配列として値を返されると言う事。
//	以下の内容は、getaddrinfo()実行後に格納される。
//	addressinfo.ai_addrlen;					//以下のアドレスの長さ。
//	addressinfo.ai_addr;						//アドレスへのポインタ
//	addressinfo.ai_canonname;				//ai_flagsにAI_CANONNAME フラグが含まれている場合、返されるリストの最初の addrinfo 構造体の ai_canonname フィールドはホストの公式な名前を指すように設定される。
//	addressinfo.ai_next;						//リストの次のデータへのアドレス。

	int RESULT = getaddrinfo((this->hostNameOrAddress).c_str(), (this->service).c_str(), &addressinfo, &addressinfo_result );
//	int RESULT = getaddrinfo((this->hostNameOrAddress).c_str(), (this->service).c_str(), &addressinfo, &&addressinfo );//addressinfoと同一にしても問題無い??(後で確認する。)
	if(RESULT!=0){
		printf("getaddrinfo was failed : %s\n",gai_strerror(RESULT));	//gai_strerror()関数は、数値を可読可能なエラーコードに変換してくれる……はず。
		return false;
	}
	
	struct addrinfo *addressinfo_result_buf;
	
	for(addressinfo_result_buf  = addressinfo_result    ->ai_next;	//解放する必要があるのでコピーしておく。
	    addressinfo_result_buf != NULL;								//次が無くなるまでループを回す。
	    addressinfo_result_buf  = addressinfo_result_buf->ai_next	//次のアドレスに書き換える。
	){
		//ソケットの生成
		//printf("Generate socket.\n");
		this->sock = socket(addressinfo_result_buf->ai_family, addressinfo_result_buf->ai_socktype, addressinfo_result_buf->ai_protocol);

		if(this->sock!=-1){
			//this->sock!=-1

			//回線の接続
			if(connect(this->sock, addressinfo_result_buf->ai_addr, addressinfo_result_buf->ai_addrlen)==0){ //connect():戻り値は、成功すると0、失敗すると-1となる。
				//printf("Connection Success\n");
				break;	//接続に成功したので、for文を抜けて次の処理へ移行する。
			}
			printf("connect() failed\n");
			close(this->sock);	//失敗したのでソケットを閉じる。(socket()関数に失敗した場合は、そもそも閉じるソケットが無いと思われるので、何もしない。)
		}else{
			//this->sock==-1
			//エラーが発生したため、現在の設定(addressinfo_result_buf)でのsocket()関数を終了する。(forの次の値へ)
			printf("socket() failed\n");
		}
	}

	if(addressinfo_result_buf==NULL){
		//全て失敗した場合。
		printf("All connection failed\n");

		//close(this->sock);					//全て失敗しているなら、socketはそもそも開いていないハズなので、閉じる必要も無い。
		freeaddrinfo(addressinfo_result);
		return false;
	}
	freeaddrinfo(addressinfo_result);	//もう必要無いので解放してしまう。
	
	
	//ここからOpenSSL
		//初期化
	SSL_load_error_strings();
	SSL_library_init();

		//暗号化の設定
//	this->ctx = SSL_CTX_new( SSLv2_client_method());	// SSLver2だけを使用する
//	this->ctx = SSL_CTX_new( SSLv3_client_method());	// SSLver3だけを使用する
//	this->ctx = SSL_CTX_new( TLSv1_client_method());	// TLSver1だけを使用する
	this->ctx = SSL_CTX_new(SSLv23_client_method());	// SSLv2,SSLv3,TLSv1すべてだけを使用する

	this->ssl = SSL_new(this->ctx);
	
		//SSL通信の開始
	SSL_set_fd(this->ssl, this->sock);	//OpenSSLにソケットを渡す。
	SSL_connect(this->ssl);
	
	return true;
}

int sstd::sockSSL::send(const std::string& msg){
	return SSL_write(this->ssl, msg.c_str(), msg.length());
}
int sstd::sockSSL::send_withPrint(const std::string& msg){
	printf("Send Data >> %s", msg.c_str());
	return send(msg);
}

//int sockSSL::Make_Connection_ReturnReceiveMessage(){
std::string sstd::sockSSL::receive(bool& result){
	result=true;
	
	std::string receivedMsg;
	char buf[1024*1024];
	for(int previous_readSize=0, readSize=1;
			previous_readSize != readSize;
			previous_readSize  = readSize	)
	{
		memset(buf, 0, sizeof(buf));
		readSize = SSL_read(this->ssl, buf, sizeof(buf)-1);
		buf[readSize] = '\0';

		if(readSize<0){ result=false; return std::string(""); }
		
		receivedMsg += buf;
	}
	return receivedMsg;
}

void sstd::sockSSL::sstd_sockSSL_close(){
	
	//終了処理
	SSL_shutdown(this->ssl); // SSL_connect()の終了
	SSL_free    (this->ssl); // SSL_new()    で確保した領域を解放する。
	SSL_CTX_free(this->ctx); // SSL_CTX_new()で確保した領域を解放する。
	
	//回線の切断
	close(this->sock);
}
