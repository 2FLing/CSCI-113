//*********************************************************************
//*	This program calculate the product of two numbers				  *
//*	by using the principle of Booth's multiplication algorithm:		  *
//*	Author: MingkuanPang											  *
//*	Date: 3/15/2021													  *
//*********************************************************************
#include<string>
#include<iostream>
#include<stdio.h>
#include<iomanip>
using namespace std;
string alu(string, string, int, string);
string adder(string, string);
string invert(string);
string shift(string&,string&,string&);
string BoothMul(string, string);
void display(string, string, string, string, string);
int main()
{
	string MD, MQ;
	while (true)
	{
		try
		{
			cout << "Please Enter MD(multiplicand) -- Type in 'q' to exit:";
			cin >> MD;
			if (MD == "q")
				break;
			if (MD.length() != 16)
				throw 1;
			cout << endl;
			cout << "Please Enter MQ(multiplier) -- Type in 'q' to exit:";
			cin >> MQ;
			if (MQ == "q")
				break;
			if (MQ.length() != 16)
				throw 1;
			cout << "Product is: " << BoothMul(MD, MQ) << endl;
		}
		catch (int e)
		{
			cout << "The digit of the number must be 16." << endl;
		}
	}
	return 0;
}

//This function calculate the sum or the differece of two binary numbers
//by using the algorithm in ALU
string alu(string a, string b, int binvert, string op)
{
	string res;
	if (binvert)
		b = invert(b); // if binvert == 1 then switch b to 2s complement
	if (op == "10") // if op=="10" then calculate a+b
		res = adder(a, b);
	else
		res = adder(a, invert(b)); // otherwise calculate a+(-b)

	return res;
}

//This function calculate the sum of  two binary numbers
//by using the algorithm in alu adder.
string adder(string a, string b)
{
	int i = a.length()-1, j = b.length()-1;
	int carry = 0;
	string res = "";
	while (i >= 0 or j >= 0)
	{
		int sum = 0;
		if (i >= 0)
			sum += a[i--] - '0';
		if (j >= 0)
			sum += b[j--] - '0';
		sum += carry;
		carry = sum > 1 ? 1 : 0;
		res += to_string(sum % 2);
	}
	reverse(res.begin(), res.end());
	return res;
}
//This function swtich a binary number to it's 2s complement form.
string invert(string a)
{
	for (int i = 0; i < a.length(); i++)
	{
		a[i] = a[i] == '0' ? '1' : '0';
	}
	return adder(a, "1");
}
//This function shift two binary numbers to the right by one bit
//Then, set the third number to the last bit of the second number 
//before it shifted
string shift(string& a,string& b,string& c)
{
	string op = a + b + c;
	string res;
	res = op[0];//add the sign bit to the most left.
	for (int i=0;i<op.length()-1;i++)
	{
		res += op[i];// add the original bits except the last bit.
	}
	a = res.substr(0, a.length());
	b = res.substr(16, b.length());
	c = res[res.length() - 1];
	return res;
}

void display(string a, string b, string c, string d, string e)
{
	cout << a << setw(30) << b << setw(22) << c << setw(22) << d << setw(12) << e << endl;
}

// This function calculte the product of two binary numbers by using the
// Booth's multiplication algorithm.
string BoothMul(string MD, string MQ)
{
	string CycleCounter = "1111";
	string zero = "0000000000000000"; //0 in 16 bits binary form
	string ac;
	string mq_1 = "0"; 
	string op;
	string product;
	int lenMQ = MQ.length();
	ac = zero;
	cout << "Cycle-counter" <<setw(15)<<"MD" <<setw(20)<< "AC" << setw(20) << "MQ" << setw(23) << "MQ-1"<<endl;
	cout << "---------------------------------------------------------------------------------------------------" << endl;
	display(CycleCounter, MD, ac, MQ, mq_1);
	for(int i=0;i<16;i++)
	{
		
		op = MQ[lenMQ - 1] + mq_1;
		if (op == "00")
		{
			ac = alu(ac, zero, 0, "10"); //if op=="00" then ac = ac + 0
		}
		else if (op == "01")
		{
			ac = alu(ac, MD, 0, "10");// if op == "01" then ac = ac + md
		}
		else if (op == "10")
		{
			ac = alu(ac, MD, 1, "10");// if op == "10" then ac = ac - md
		}
		else
		{
			ac = alu(ac, zero, 0, "10");// if op == "11" then ac = ac + 0
		}
		display(CycleCounter, MD, ac, MQ, mq_1);
		shift(ac, MQ, mq_1);
		display(CycleCounter, MD, ac, MQ, mq_1);
		cout << endl;
		CycleCounter = alu(CycleCounter, "0001", 1, "10"); // CycleCounter--
	}
	product = ac + MQ;
	return product;
}