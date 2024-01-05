#include <iostream>
#include <windows.h>
using namespace std;

int main()
{
  // string toRender ="";
  const int textNums = 3;
  string texts[textNums] = {"Yo man wassup, waya kana sanga e jani, ado pata di nalagi,za messagetext ya video call khu kawa kana da adeer ghalat kaar de yar", "mara bus sa uwayu yar deer zyat masrfuiat bas mazhga me khaarba shawi er yar nust universitty ta bus, zaanta lumber 1 wai nu", "da wala daodoajdoawjdojasodmasodmosadasd"};

  for (int i = 0; i < textNums; i++)
  {
    if (i != 0)
    {
      system("pause>null");
    }
    for (int j = 0; j < texts[i].length(); j++)
    {

      cout << texts[i][j];
      Sleep(20);
    }
    cout << endl;
  }
  return 0;
}