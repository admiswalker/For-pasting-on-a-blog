struct sMail{
	std::string usr;     // usr name
	std::string domain;  // domain
	std::string pass;    // password
//	std::string from;    // メールの送信元。[usr]より自動生成
	std::string to;      // メールの送信先
	std::string subject; // メールの件名
	std::string data;    // メールの本文(今回はHTMLmailなので、HTMLを記述)
};

void sendMail                  (struct sMail& mail);
//void sendMail_withPrint        (struct sMail& mail);
void sendMail_of_HTML          (struct sMail& mail);
void sendMail_of_HTML_withPrint(struct sMail& mail);

