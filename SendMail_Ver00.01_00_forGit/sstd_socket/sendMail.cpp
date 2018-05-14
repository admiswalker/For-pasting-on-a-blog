#include <sstd/sstd.hpp>
#include "socket.hpp"
#include "sendMail.hpp"

bool sendMail(struct sMail& mail){
	sstd::sockSSL sock(sstd::ssprintf("smtp.%s", mail.domain.c_str()).c_str(), "465");
	
	bool ret;
	if(!sock.open()){return false;}                                                   sock.recv(ret); if(!ret){return false;}
	if( sock.send("EHLO localhost\r\n"                           )<=0){return false;} sock.recv(ret); if(!ret){return false;}
	if( sock.send("AUTH LOGIN\r\n"                               )<=0){return false;} sock.recv(ret); if(!ret){return false;}
	if( sock.send(sstd::base64_encode(mail.usr)+"\r\n"           )<=0){return false;} sock.recv(ret); if(!ret){return false;} // mail User ID
	if( sock.send(sstd::base64_encode(mail.pass)+"\r\n"          )<=0){return false;} sock.recv(ret); if(!ret){return false;} // mail pass
	if( sock.send("MAIL FROM: <"+mail.usr+'@'+mail.domain+">\r\n")<=0){return false;} sock.recv(ret); if(!ret){return false;}
	if( sock.send("RCPT TO: <"+mail.to+">\r\n"                   )<=0){return false;} sock.recv(ret); if(!ret){return false;}
	if( sock.send("DATA\r\n"                                     )<=0){return false;} sock.recv(ret); if(!ret){return false;}
	
	std::string buf;
	buf  = "Subject: =?UTF-8?B?"+sstd::base64_encode(mail.subject)+"?=\r\n";
	
	buf += "Mime-Version: 1.0;\r\n";
	buf += "Content-Type: text/plain; charset=\"UTF-8\";\r\n";
	buf += "Content-Transfer-Encoding: 7bit;\r\n";
	buf += "\r\n";
	buf += mail.data+"\r\n";
	buf += ".\r\n";
	if( sock.send(buf                                            )<=0){return false;} sock.recv(ret); if(!ret){return false;}

	return true;
}
bool sendMail_withPrint(struct sMail& mail){
	sstd::sockSSL sock(sstd::ssprintf("smtp.%s", mail.domain.c_str()).c_str(), "465");
	
	bool ret;
	if(!sock.open()){return false;}                                                             sstd::print(sock.recv(ret)); if(!ret){return false;}
	if( sock.send_withPrint("EHLO localhost\r\n"                           )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}
	if( sock.send_withPrint("AUTH LOGIN\r\n"                               )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}
	printf("Sending Data >> %s\n", mail.usr.c_str());
	if( sock.send_withPrint(sstd::base64_encode(mail.usr)+"\r\n"           )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;} // mail User ID
	printf("Sending Data >> %s\n", mail.pass.c_str());
	if( sock.send_withPrint(sstd::base64_encode(mail.pass)+"\r\n"          )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;} // mail pass
	if( sock.send_withPrint("MAIL FROM: <"+mail.usr+'@'+mail.domain+">\r\n")<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}
	if( sock.send_withPrint("RCPT TO: <"+mail.to+">\r\n"                   )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}
	if( sock.send_withPrint("DATA\r\n"                                     )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}
	
	std::string buf;
	buf  = "Subject: =?UTF-8?B?"+sstd::base64_encode(mail.subject)+"?=\r\n";
	
	buf += "Mime-Version: 1.0;\r\n";
	buf += "Content-Type: text/plain; charset=\"UTF-8\";\r\n";
	buf += "Content-Transfer-Encoding: 7bit;\r\n";
	buf += "\r\n";
	buf += mail.data+"\r\n";
	buf += ".\r\n";
	if( sock.send_withPrint(buf                                            )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}

	return true;
}
bool sendMail_of_HTML(struct sMail& mail){
	sstd::sockSSL sock(sstd::ssprintf("smtp.%s", mail.domain.c_str()).c_str(), "465");
	
	bool ret;
	if(!sock.open()){return false;}                                                   sock.recv(ret); if(!ret){return false;}
	if( sock.send("EHLO localhost\r\n"                           )<=0){return false;} sock.recv(ret); if(!ret){return false;}
	if( sock.send("AUTH LOGIN\r\n"                               )<=0){return false;} sock.recv(ret); if(!ret){return false;}
	if( sock.send(sstd::base64_encode(mail.usr)+"\r\n"           )<=0){return false;} sock.recv(ret); if(!ret){return false;} // mail User ID
	if( sock.send(sstd::base64_encode(mail.pass)+"\r\n"          )<=0){return false;} sock.recv(ret); if(!ret){return false;} // mail pass
	if( sock.send("MAIL FROM: <"+mail.usr+'@'+mail.domain+">\r\n")<=0){return false;} sock.recv(ret); if(!ret){return false;}
	if( sock.send("RCPT TO: <"+mail.to+">\r\n"                   )<=0){return false;} sock.recv(ret); if(!ret){return false;}
	if( sock.send("DATA\r\n"                                     )<=0){return false;} sock.recv(ret); if(!ret){return false;}
	
	std::string buf;
	buf  = "Subject: =?UTF-8?B?"+sstd::base64_encode(mail.subject)+"?=\r\n";
	
	buf += "Mime-Version: 1.0;\r\n";
	buf += "Content-Type: text/html; charset=\"UTF-8\";\r\n";
	buf += "Content-Transfer-Encoding: 7bit;\r\n";
	buf += "\r\n";
	buf += mail.data+"\r\n";
	buf += ".\r\n";
	if( sock.send(buf                                            )<=0){return false;} sock.recv(ret); if(!ret){return false;}
	
	return true;
}
bool sendMail_of_HTML_withPrint(struct sMail& mail){
	sstd::sockSSL sock(sstd::ssprintf("smtp.%s", mail.domain.c_str()).c_str(), "465");
	// poart number >> 465: SMTP over SSL
	//                 587: TLS
	
	bool ret;
	if(!sock.open()){return false;}                                                             sstd::print(sock.recv(ret)); if(!ret){return false;}
	if( sock.send_withPrint("EHLO localhost\r\n"                           )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}
	if( sock.send_withPrint("AUTH LOGIN\r\n"                               )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}
	printf("Sending Data >> %s\n", mail.usr.c_str());
	if( sock.send_withPrint(sstd::base64_encode(mail.usr)+"\r\n"           )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;} // mail User ID
	printf("Sending Data >> %s\n", mail.pass.c_str());
	if( sock.send_withPrint(sstd::base64_encode(mail.pass)+"\r\n"          )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;} // mail pass
	if( sock.send_withPrint("MAIL FROM: <"+mail.usr+'@'+mail.domain+">\r\n")<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}
	if( sock.send_withPrint("RCPT TO: <"+mail.to+">\r\n"                   )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}
	if( sock.send_withPrint("DATA\r\n"                                     )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}
	
	//std::string Subject_str = "TESTING_NOW_テスト投稿_＿（全角アンダーバーとか入れてみる。）＿（全角アンダーバーとか入れてみる。）文字数制限を確認する為に、長いタイトルを送信してみる。たしか、約80文字以上に長いタイトルの場合は、文字ごとにまとめて改行を施すなど、多少面倒な操作が必要とされるらしい。まだ長さが足りないので、もう少し文字数を増やして見る。果たしてちゃんと（？）失敗するだろうか？いやいやぁ、まだまだこの程度の長さでは全くもう失敗しないので、もう少しもうだいぶ長くしてみようと思うんだけど、これ本当に失敗するのかな？Gmailが優秀だから失敗しないのか、それとも、そもそも最近の規格では考える必要が無くなったのか、その辺りをはっきりさせたいのだが、そろそろキーボードを叩くのが面倒になってきた。(半角『』)結局失敗しなかった……。もう成功って事で良いよね？??？";	//Gmailの送信箱や受信箱では、おおよそ167文字以上からの表示がバグる。ただし、Blogger側での表示は正常。
	//sock.SendMsg  = "Subject: \r\n";
	//sock.SendMsg  = "Subject: =?ISO-2022-JP?Q?XXXXXXX?=\r\n";
	//sock.SendMsg  = "Subject: =?ISO-2022-JP?B?XXXXXXX?=\r\n";
	//sock.SendMsg  = "Subject: =?UTF-8?Q?";
	std::string buf;
	buf  = "Subject: =?UTF-8?B?"+sstd::base64_encode(mail.subject)+"?=\r\n";
	
	buf += "Mime-Version: 1.0;\r\n";
//	buf += "Content-Type: text/html; charset=\"ISO-8859-1\";\r\n";
	buf += "Content-Type: text/html; charset=\"UTF-8\";\r\n";
	buf += "Content-Transfer-Encoding: 7bit;\r\n";
	buf += "\r\n";
	buf += mail.data+"\r\n";
	buf += ".\r\n";
	if( sock.send_withPrint(buf                                            )<=0){return false;} sstd::print(sock.recv(ret)); if(!ret){return false;}
	
	return true;
}

/*
220 smtp.gmail.com ESMTP XXXXXXXXXXXXXXXXXXX - gsmtp

Send Data >> EHLO localhost
250-smtp.gmail.com at your service, [XXX.XXX.XXX.XXX]
250-SIZE 35882577
250-8BITMIME
250-AUTH LOGIN PLAIN XOAUTH2 PLAIN-CLIENTTOKEN OAUTHBEARER XOAUTH
250-ENHANCEDSTATUSCODES
250-PIPELINING
250-CHUNKING
250 SMTPUTF8

Send Data >> AUTH LOGIN
334 VXNlcm5hbWU6

Send Data >> [base64Encoded_usrName]
334 UGFzc3dvcmQ6

Send Data >> [base64Encoded_passWord]
235 2.7.0 Accepted

Send Data >> MAIL FROM: <[usrName]@[domain]>
250 2.1.0 OK XXXXXXXXXXXXXXXXXXX - gsmtp

Send Data >> RCPT TO: <[mail.to]>
250 2.1.5 OK XXXXXXXXXXXXXXXXXXX - gsmtp

Send Data >> DATA
354  Go ahead XXXXXXXXXXXXXXXXXXX - gsmtp

Send Data >> Subject: =?UTF-8?B?VEVTVElOR19OT1df44OG44K544OI5oqV56i/X+ODnuODq+ODgeODkOOCpOODiOOCs+ODvOODieOCguiHqueUseiHquWcqCEh?=
Mime-Version: 1.0;
Content-Type: text/html; charset="UTF-8";
Content-Transfer-Encoding: 7bit;

<br/>これは，HTML メールの送信テストです．<br/>■■■ <b><u>タイトル</u></b> ■■■<br/><ul><li>項目 1. </li><li>項目 2. </li></ul><br/><hr/><br/>abc あいう<br/><br/>
.
250 2.0.0 OK 1522244454 XXXXXXXXXXXXXXXXXXX - gsmtp
*/



