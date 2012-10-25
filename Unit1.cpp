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
UnicodeString Within(UnicodeString ,UnicodeString , UnicodeString )  ;
int EPos(UnicodeString , UnicodeString )  ;
UnicodeString AfterTail(UnicodeString, UnicodeString);
UnicodeString WithinTails(UnicodeString,UnicodeString, UnicodeString, int);
UnicodeString RemoveHead(UnicodeString,UnicodeString);
UnicodeString AfterNTail(UnicodeString, UnicodeString, int);
UnicodeString * DivStr(UnicodeString WholeStr, UnicodeString Archor);
void testP(int);
void testPP(int*);

TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
	: TForm(Owner)
{
	Form1->Memo1->Text="";
}

void testP(int p){p=100;}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
	UnicodeString *str;
	str	= DivStr("<abcdefghijklmn>" , "f");
	Report(0, str[0]);
	Report(0, str[1]);
}

// Return the position for the Nth str in body. Body: str str str str ...
int Search(UnicodeString body, UnicodeString part,int index)
{
	UnicodeString bodyCopy = body;
	int position 		   = 1;//body.Pos(part);
	int partL 			   = part.Length();
	int posCopy			   = position;
	int count			   = 0;
	while(count!= index-1)
	{
		count++;
		if (posCopy!=0) {
			bodyCopy.Delete(posCopy,partL);
			position+=partL;
			//position--;
			posCopy = bodyCopy.Pos(part);
		}
	}
	position += bodyCopy.Pos(part);
	return position - 1;
}

// Return the count duplicated str in body.
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

// Return the str with in head and tail. Body: headstrtail
UnicodeString Within(UnicodeString body,UnicodeString head, UnicodeString tail)
{
	if (head!=tail)
	{
		return body.SubString(body.Pos(head)+head.Length(), body.Pos(tail)-body.Pos(head)-head.Length());
	}
	else if (head==tail)
	{
		UnicodeString temp = body;
		temp.Delete(1,temp.Pos(head)-1);
		temp.Delete(1,head.Length());
		temp.Delete(temp.Pos(tail),temp.Length()-temp.Pos(tail)+1);
		return temp;
	}
}

// Return the position of the ending char of part in body.
int EPos(UnicodeString body, UnicodeString part)
{
	return body.Pos(part)+ part.Length()-1;
}

// Return str after the tail.
UnicodeString AfterTail(UnicodeString body, UnicodeString tail)
{
	return body.SubString(EPos(body,tail)+ 1,body.Length()-EPos(body,tail));
}

// Return str after head and before the Nth tail.
UnicodeString WithinTails(UnicodeString body,UnicodeString head, UnicodeString tail, int tailIndex)
{
	int count= 0;
	UnicodeString temp = body;
	if (CountPart(body,tail)==0)
	{
		return body;
	}
	else if (CountPart(body,tail)==1)
	{
		return Within(body,head,tail);
	 }
	 else if (CountPart(body, tail)>1)
	 {
		return body.SubString(body.Pos(head)+head.Length(), Search(body,tail,tailIndex)-body.Pos(head)-head.Length() );
	  }
}

// Remove char before string
UnicodeString RemoveHead(UnicodeString body,UnicodeString head)
{
	UnicodeString temp = body;
	return temp.Delete(1, temp.Pos(head)-1);
}

// Remove chars after the Nth tail.
UnicodeString AfterNTail(UnicodeString body, UnicodeString tail, int index)
{
	UnicodeString temp = body;
	while(index>=0)
	{
		temp = AfterTail(temp,tail);
		index--;
	}
	return temp;
}

// Divide a string into two parts.
UnicodeString * DivStr(UnicodeString WholeStr, UnicodeString Archor)
{
	int CutPos;
	int StrLength;
	UnicodeString *sArray;

	sArray 	  = new UnicodeString[2];
	CutPos 	  = WholeStr.Pos(Archor);
	StrLength = WholeStr.Length();

	sArray[0] = WholeStr.SubString(1,CutPos-1);
	sArray[1] = WholeStr.SubString(CutPos + 1, StrLength - CutPos);

	return sArray;
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