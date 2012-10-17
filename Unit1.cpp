//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
void Report(int, UnicodeString);
int Search(UnicodeString, UnicodeString,int);
int CountPart(UnicodeString,UnicodeString)  ;
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Form1->Memo1->Text="";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
UnicodeString str = "12345678901234567890     ";
Report(999, "123 inside " + str+ " located at " + str.Pos("123"));
// CAREFUL: the result is 13 not 10
Report(999, "123 inside search from right" + str+ " located at " + str.LastDelimiter("123"));
// CAREFUL: str.Delete is performed before passing to the report, so str is changed before passing.
Report(999, "Delete 123 from " + str+ " result is " + str.Delete(1,3) );
// CAREFUL: The followings are the same.
Report(999, "Substring from 0 with length 4 is of " + str+ " is " + str.SubString(0,4));
Report(999, "Substring from 1 with length 4 is of " + str+ " is " + str.SubString(1,4));
Report(999, "The 5th character in  " + str+ " is " + str[5]);
// CAREFUL: Trimming and SetLength does NOT modify the original string, you have to set it yourself
Report(999, "Before trimming the length of "+ str + " is " + str.Length());
str = str.Trim();
Report(999, "After trimming the length of "+ str + " is " + str.Length());
str = str.SetLength(12);
Report(999, "After set length=12 the length of "+ str + " is " + str.Length());


/*                                                                              */

    str = "12345678901234567890     ";
	Report(Search(str,"123",2), "The second 123 is ");

str = "12345678901234567890123456789012345678901234567890";
Report(Search(str,"123",4), "The forth 123 is ");
Report(999, str); // the orginal string is not changed
Report(CountPart(str,"123"), "123 appears times of ");
}

int Search(UnicodeString body, UnicodeString part,int index)
{
	UnicodeString bodyCopy = body;
	int position 		   = body.Pos(part);
	int partL 			   = part.Length();
	int posCopy			   = position;
	int count			   = 0;
	while(count!= index-1)
	{
		count++;
		if (posCopy!=0) {
			bodyCopy.Delete(posCopy,partL);
			position+=partL;
			posCopy = bodyCopy.Pos(part);
		}
	}
	position += bodyCopy.Pos(part);
	return position - 1;
}

int CountPart(UnicodeString body,UnicodeString part)
{
	int count=0;
	UnicodeString bodyCopy = body;
	while (bodyCopy.Pos(part)!=0)
	{
		 bodyCopy = bodyCopy.Delete(bodyCopy.Pos(part),part.Length());
		 count++;
	}
	return count;
}


//---------------------------------------------------------------------------

void Report(int v,UnicodeString s)
{
  if (v==999)
  {
	Form1->Memo1->Text = Form1->Memo1->Text + s + "\r\n\r\n";
  }
  else
  {
	Form1->Memo1->Text = Form1->Memo1->Text + s + " : " + IntToStr(v)+ "\r\n\r\n";
  }
}