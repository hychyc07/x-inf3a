
#ifndef __fhead_h__
#define __fhead_h__

/*------------ ヘッダー検索システ��E  C++ 版 ------------

��E使い方 ��E

	setfile fobj;

	fobj.open("fname");          ファイ��E鬟�ープンす��E
	
	fobj.find_header("header");  ヘッダー（1行）を見つけ��E
	fobj.find_word("word");      単��E紛�白で区切ら��E進源�列）を見つけ��E

	i = fobj.get_int();          整数を読み込��E
	f = fobj.get_float();        実数を読み込��E
	d = fobj.get_dluble();       倍精度実数を読み込��E
	string = fobj.get_string()   C++ の文字列を読み込��E
	string = fobj.get_line()     1 行読み込��E( 改行記号は李脆す )

	fobj.get_string(str* str,int len)  C の文字列を読み込��E
	fobj.get_line(str* str, int len)   1 行読み込��E( 改行記号は李脆す )

	fobj.close();

	設��E侫．ぅ�E涼罎縫灰瓮鵐箸鯑���E�E海箸�出来��E
	';' と改行マークの間をコメントとみなす。

	区切��E源�E: 「改行」「タブ」「空白」「; で始ま��E灰瓮鵐函�

 ver 1.0  1992?       C 版の初版笹椪

     2.0  2003.8.12   C++ version
                      メソッドの名前などインターフェースを変更
                      get_string で読み込みの途中に最大文字列をオーバー
                      したとき、読み込み中の文字列はスキップす��E

	 2.1       8.14   複素数は stream からしか読みと��E覆い燭�E
	                  FILE ではなくifstream を使う。

	 2.2       9.3    g++ 2.95.3 の getline のバグを回避す��E燭�E
                      my_getline を自分で実装す��E�

     2.3  2007.10.23  ・ファイ��E┘鵐匹謀�達したときの my_getline の返��E佑�E
                        EOF と錯覚していた箇所を修正（正しい値は 0）
                      ・get_double などで、「ret = 」を忘��E討い燭里鮟だ�
                      ・Windows でも動笹盛��E茲Δ� '\r' に対す��E萢�を付加

     2.4       11.13  ifstream の使い方が効醒ていたのを修正
                      fp.open の��E漫▲侫．ぅ�E�開いたか否かは is_open() で
                      判定す��E�要があ��E�

��E丁盲！��E

     g++ 2.95.3 の getline は maxlen を超え��E圓鯑匹濆�んだとき、
     以後の処理がおかしくな��E�次回以降の読み込みでは str には何��E
     入らず、fp.eof() ��Etrue にならない。無限��E璽廚砲覆�E�
*/

#include <stdio.h>
#include <string>

#include <fstream>

using namespace std;

class setfile{
public:
	setfile();
	setfile(const char fname[]);
	int   open(const char fname[]);
	void  close();

	int  find_header(const char keyword[]);
	int  find_word  (const char keyword[]);

	int    get_int   ();
	float  get_float ();
	double get_double();
	string get_string();
	string get_line();    // str.c_str() は const であり、こ��E悩い�E
                          // ときは下の get_line(str[],len) を用い��E
	int    get_string(char str[], int maxlen);
	int    get_line(char str[], int maxlen);

	ifstream fp;  // 本当は private にしたいが、フィー��E匹瞭匹濆�みなど
                  // 外からアクセスしたい��E腓發△�E里� public にす��E
	
private:
	int  my_getline(char str[], int maxlen);
	int  open_yn;
	int  skip_comment();
	void rm_right_space(char str[]);
	void check_int(char str[]);
	void check_double(char str[]);
};

#endif
