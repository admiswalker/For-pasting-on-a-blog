#define use_sstd_measureTime
#include <sstd/sstd.hpp>
#include "./sstd_socket/sendMail.hpp"

int main(){
	printf("■ measureTime_start---------------\n\n"); time_m timem; sstd::measureTime_start(timem);
	
	struct sMail mail;
	mail.usr     = "usrName";
	mail.domain  = "gmail.com";
	mail.pass    = "passWord";
	mail.to      = "usrName@domain";
	mail.subject = "TESTING_NOW_テスト投稿_マルチバイトコードも自由自在!!";

	{
		mail.data    = "This is a test of plain text mail.\r\n";
		mail.data   += "\r\n";
		mail.data   += "これは，プレーンテキストメールの送信テストです．<br/>\r\n";
		mail.data   += "■■■ <b><u>タイトル</u></b> ■■■<br/>\r\n";
		mail.data   += "<ul>\r\n";
		mail.data   += "<li>項目 1. </li>\r\n";
		mail.data   += "<li>項目 2. </li>\r\n";
		mail.data   += "</ul>\r\n";
		mail.data   += "<br/>\r\n";
		mail.data   += "<hr/>\r\n";
		mail.data   += "<br/>\r\n";
		mail.data   += "abc あいう<br/>\r\n";
		mail.data   += "<br/>\r\n";
	
//		if(!sendMail          (mail)){ sstd::pdbg("ERROR: sendMail() was failed.\n"); }
		if(!sendMail_withPrint(mail)){ sstd::pdbg("ERROR: sendMail_withPrint() was failed.\n"); }
	}
	//*
	{	
		mail.data    = "This is a test of HTML mail.<br/>";
		mail.data    = "<br/>";
		mail.data   += "これは，HTML メールの送信テストです．<br/>";
		mail.data   += "■■■ <b><u>タイトル</u></b> ■■■<br/>";
		mail.data   += "<ul>";
		mail.data   += "<li>項目 1. </li>";
		mail.data   += "<li>項目 2. </li>";
		mail.data   += "</ul>";
		mail.data   += "<br/>";
		mail.data   += "<hr/>";
		mail.data   += "<br/>";
		mail.data   += "abc あいう<br/>";
		mail.data   += "<br/>";
	
//		if(!sendMail_of_HTML          (mail)){ sstd::pdbg("ERROR: sendMail_of_HTML() was failed.\n"); }
		if(!sendMail_of_HTML_withPrint(mail)){ sstd::pdbg("ERROR: sendMail_of_HTML_withPrint() was failed.\n"); }
	}
	//*/
	
	printf("\n■ measureTime_stop----------------\n"); sstd::measureTime_stop(timem); sstd::pauseIfWin32();
	return 0;
}

