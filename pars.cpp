#include "pars.h"
#include <stack>
#include <string>

Parser::Parser()
{
	
	//.. initialize all the variables, the left and up strings and 
	//    the parse table
	token=0;
	ileft=0;
	iup=0;
	read_flag=false;
	size_up=75;
	input_flag=true;
	call_marker=false;//it is initially set false when the 1st marker comes it is set to true
	marker=" ";

	// initialiaze the non-terminal string
	left[0]="f";		left[1]="f'";
	left[2]="t" ;       left[3]="t'"; 
	left[4]="s_e";      left[5]="s_e'";
	left[6]="e" ;       left[7]="e'";
	left[8]="e_l";      left[9]="e_l'";
	left[10]="p_s";     left[11]="p_s'";
	left[12]="v";       left[13]= "v'";
	left[14]="st";      left[15]="st'";
	left[16]="st_l";    left[17]="st_l'";
	left[18]="op_s";    left[19]="c_s";
	left[20]="pr_l";    left[21]="pr_l'";
	left[22]="ar";      left[23]="sub_h";
	left[24]="sub_dec"; left[25]="sub_decs";
	left[26]="sub_decs'"; 
	left[27]="st_tp" ;  
	left[28]="tp";      left[29]="dec";
	left[30]="dec'";    left[31]="id_l" ;
	left[32]="id_l'";   
	left[33]="start";	left[34]="ad";// addop
	left[35]="mulop";	left[36]="as";// assignop
	left[37]="not";		left[38]="s"; //  sign
	left[39]="relop";	left[40]="num";

	// initialiaze the terminal string
	up[0]="+";			up[1]="-";
	up[2]="!";          up[3]="(";
	up[4]=")";			up[5]="id";
	up[6]="{";			up[7]="[";
	up[8]="]";			up[9]="}";
	up[10]="while";		up[11]="do";
	up[12]="if";        up[13]="else";
	up[14]="then";		up[15]=":=";
	up[16]="function";  up[17]="procedure";
	up[18]="integer";   up[19]="real";
	up[20]="array";		up[21]="of";
	up[22]="var";		up[23]="program";
	up[24]=";";			up[25]=":";
	up[26]=",";			up[27]="int_num";
	up[28]="float_num"; up[29]="or";
	up[30]="*";
	up[31]="/";			up[32]="and";
	up[33]="mod";		up[34]="=";
	up[35]="<>";		up[36]="<";
	up[37]="<=";		up[38]=">";
	up[39]=">=";		up[40]="<<";
	up[41]=">>";		up[42]="..";

	// markers saved as terminals

	up[43]="m3";// marker 3 for declararion
	up[44]="m4";//to set & in stck
	up[45]="m1";//for :=
	up[46]="m2";//for addop
	up[47]="m5";//for function arguements
	up[48]="m6";//for making the parameterlist
	up[49]="m7";//for making the input to the symbol table false
	up[50]="m8";//for mking above flag true
	up[51]="m9";//for mulop
	up[52]="m10";//for relop
	up[53]="m11";//for write
	up[54]="m12";//for read
	
	up[55]="m13";//for while to put line number on the bkpch stack
	up[56]="m14";//for while to backpatch
	
	up[57]="m15";//speacila marker for if 
	up[58]="m16";//speacila marker for if 
	
	up[59]="m17";//declares a new avltree and put it on stak 
	up[60]="m18";//pops the avltreee of ending fn from stack
	
	up[61]="m19";//put line num on stk fow while
	up[62]="m20";//pop line num and write goto for while

	up[63]="m21";//makes a new var for intgr
	up[64]="m22";//makes a new var for float
	
	up[65]="m23";//to call actiuvation record

	up[66]="m24";//to have strta stmt at bgning
	up[67]="m25";//to bckpch tht start symbol

	up[68]="m26";//for not oprator
	up[69]="m27";//to check whther the called function exist or not
	up[70]="m28";//to pur end at the end of code file
	
	up[71]="m29";//to nndo the function call
	up[72]="m30";//to handle function call of a 0 parm function
	up[73]="m31";//to handle multi read
	up[74]="m32";// """""""
	// initialiaze the parse tabel
	//0 is used as null production
	// [0] for +, [1] for - , [2] for !,
	pars_tabl[0][0]=" ";            pars_tabl[0][1]=" ";			pars_tabl[0][2]="not f m26";
	pars_tabl[1][0]="0";		    pars_tabl[1][1]="0";			pars_tabl[1][2]=" ";
	pars_tabl[2][0]=" ";		    pars_tabl[2][1]=" ";			pars_tabl[2][2]="f t'";
	pars_tabl[3][0]="0";		    pars_tabl[3][1]="0";			pars_tabl[3][2]=" ";
	pars_tabl[4][0]="s t s_e'";		pars_tabl[4][1]="s t s_e'";		pars_tabl[4][2]="t s_e'";
	pars_tabl[5][0]="ad t s_e' m2";	pars_tabl[5][1]="ad t s_e' m2";	pars_tabl[5][2]=" ";
	pars_tabl[6][0]="s_e e'";		pars_tabl[6][1]="s_e e'";		pars_tabl[6][2]="s_e e'";
	pars_tabl[7][0]=" ";			pars_tabl[7][1]=" ";			pars_tabl[7][2]=" ";
	pars_tabl[8][0]="e e_l'";		pars_tabl[8][1]="e e_l'";		pars_tabl[8][2]="e e_l'";
	pars_tabl[9][0]=" ";			pars_tabl[9][1]=" ";			pars_tabl[9][2]=" ";
	pars_tabl[10][0]=" ";			pars_tabl[10][1]=" ";			pars_tabl[10][2]=" ";
	pars_tabl[11][0]=" ";			pars_tabl[11][1]=" ";			pars_tabl[11][2]=" ";
	pars_tabl[12][0]=" ";			pars_tabl[12][1]=" ";			pars_tabl[12][2]=" ";
	pars_tabl[13][0]=" ";			pars_tabl[13][1]=" ";			pars_tabl[13][2]=" ";
	pars_tabl[14][0]=" ";			pars_tabl[14][1]=" ";			pars_tabl[14][2]=" ";
	pars_tabl[15][0]=" ";			pars_tabl[15][1]=" ";			pars_tabl[15][2]=" ";
	pars_tabl[16][0]=" ";			pars_tabl[16][1]=" ";			pars_tabl[16][2]=" ";
	pars_tabl[17][0]=" ";			pars_tabl[17][1]=" ";			pars_tabl[17][2]=" ";
	pars_tabl[18][0]=" ";			pars_tabl[18][1]=" ";			pars_tabl[18][2]=" ";
	pars_tabl[19][0]=" ";			pars_tabl[19][1]=" ";			pars_tabl[19][2]=" ";
	pars_tabl[20][0]=" ";			pars_tabl[20][1]=" ";			pars_tabl[20][2]=" ";
	pars_tabl[21][0]=" ";			pars_tabl[21][1]=" ";			pars_tabl[21][2]=" ";
	pars_tabl[22][0]=" ";			pars_tabl[22][1]=" ";			pars_tabl[22][2]=" ";
	pars_tabl[23][0]=" ";			pars_tabl[23][1]=" ";			pars_tabl[23][2]=" ";
	pars_tabl[24][0]=" ";			pars_tabl[24][1]=" ";			pars_tabl[24][2]=" ";
	pars_tabl[25][0]=" ";			pars_tabl[25][1]=" ";			pars_tabl[25][2]=" ";
	pars_tabl[26][0]=" ";			pars_tabl[26][1]=" ";			pars_tabl[26][2]=" ";
	pars_tabl[27][0]=" ";			pars_tabl[27][1]=" ";			pars_tabl[27][2]=" ";
	pars_tabl[28][0]=" ";			pars_tabl[28][1]=" ";			pars_tabl[28][2]=" ";
	pars_tabl[29][0]=" ";			pars_tabl[29][1]=" ";			pars_tabl[29][2]=" ";
	pars_tabl[30][0]=" ";			pars_tabl[30][1]=" ";			pars_tabl[30][2]=" ";
	pars_tabl[31][0]=" ";			pars_tabl[31][1]=" ";			pars_tabl[31][2]=" ";
	pars_tabl[32][0]=" ";			pars_tabl[32][1]=" ";			pars_tabl[32][2]=" ";
	pars_tabl[33][0]=" ";			pars_tabl[33][1]=" ";			pars_tabl[33][2]=" ";
	pars_tabl[34][0]="+";			pars_tabl[34][1]="-";			pars_tabl[34][2]=" ";
	pars_tabl[35][0]=" ";			pars_tabl[35][1]=" ";			pars_tabl[35][2]=" ";
	pars_tabl[36][0]=" ";			pars_tabl[36][1]=" ";			pars_tabl[36][2]=" ";
	pars_tabl[37][0]=" ";			pars_tabl[37][1]=" ";			pars_tabl[37][2]="!";
	pars_tabl[38][0]="+";			pars_tabl[38][1]="-";			pars_tabl[38][2]=" ";
	pars_tabl[39][0]=" ";			pars_tabl[39][1]=" ";			pars_tabl[39][2]=" ";
	pars_tabl[40][0]=" ";			pars_tabl[40][0]=" ";			pars_tabl[40][0]=" ";



	// '('
	pars_tabl[0][3]="( e )";
	pars_tabl[1][3]="m29 ( e_l )";
	pars_tabl[2][3]="f t'";
	pars_tabl[3][3]=" ";
	pars_tabl[4][3]="t s_e'";
	pars_tabl[5][3]=" ";
	pars_tabl[6][3]="s_e e'";
	pars_tabl[7][3]=" ";
	pars_tabl[8][3]="e e_l'";
	pars_tabl[9][3]=" ";
	pars_tabl[10][3]=" ";
	pars_tabl[11][3]="( e_l m23 )";
	pars_tabl[12][3]=" ";
	pars_tabl[13][3]=" ";
	pars_tabl[14][3]=" ";
	pars_tabl[15][3]="m27 m4 p_s'";
	pars_tabl[16][3]=" ";
	pars_tabl[17][3]=" ";
	pars_tabl[18][3]=" ";
	pars_tabl[19][3]=" ";
	pars_tabl[20][3]=" ";
	pars_tabl[21][3]=" ";
	pars_tabl[22][3]="m4 ( pr_l )";
	pars_tabl[23][3]=" ";
	pars_tabl[24][3]=" ";
	pars_tabl[25][3]=" ";
	pars_tabl[26][3]=" ";
	pars_tabl[27][3]=" ";
	pars_tabl[28][3]=" ";
	pars_tabl[29][3]=" ";
	pars_tabl[30][3]=" ";
	pars_tabl[31][3]=" ";
	pars_tabl[32][3]=" ";
	pars_tabl[33][3]=" ";
	pars_tabl[34][3]=" ";
	pars_tabl[35][3]=" ";
	pars_tabl[36][3]=" ";
	pars_tabl[37][3]=" ";
	pars_tabl[38][3]=" ";
	pars_tabl[39][3]=" ";
	pars_tabl[40][3]=" ";
	// ')'
	pars_tabl[0][4]=" ";
	pars_tabl[1][4]="0";
	pars_tabl[2][4]=" ";
	pars_tabl[3][4]="0";
	pars_tabl[4][4]=" ";
	pars_tabl[5][4]="0";
	pars_tabl[6][4]=" ";
	pars_tabl[7][4]="0";
	pars_tabl[8][4]=" ";
	pars_tabl[9][4]="0";
	pars_tabl[10][4]=" ";
	pars_tabl[11][4]=" ";
	pars_tabl[12][4]=" ";
	pars_tabl[13][4]=" ";
	pars_tabl[14][4]=" ";
	pars_tabl[15][4]=" ";
	pars_tabl[16][4]=" ";
	pars_tabl[17][4]=" ";
	pars_tabl[18][4]=" ";
	pars_tabl[19][4]=" ";
	pars_tabl[20][4]=" ";
	pars_tabl[21][4]="0";
	pars_tabl[22][4]=" ";
	pars_tabl[23][4]=" ";
	pars_tabl[24][4]=" ";
	pars_tabl[25][4]=" ";
	pars_tabl[26][4]=" ";
	pars_tabl[27][4]=" ";
	pars_tabl[28][4]=" ";
	pars_tabl[29][4]=" ";
	pars_tabl[30][4]=" ";
	pars_tabl[31][4]=" ";
	pars_tabl[32][4]="0";
	pars_tabl[33][4]=" ";
	pars_tabl[34][4]=" ";
	pars_tabl[35][4]=" ";
	pars_tabl[36][4]=" ";
	pars_tabl[37][4]=" ";
	pars_tabl[38][4]=" ";
	pars_tabl[39][4]=" ";
	pars_tabl[40][4]=" ";
	// 'id'
	pars_tabl[0][5]="id f'";
	pars_tabl[1][5]=" ";
	pars_tabl[2][5]="f t'";
	pars_tabl[3][5]=" ";
	pars_tabl[4][5]="t s_e'";
	pars_tabl[5][5]=" ";
	pars_tabl[6][5]="s_e e'";
	pars_tabl[7][5]=" ";
	pars_tabl[8][5]="e e_l'";
	pars_tabl[9][5]=" ";
	pars_tabl[10][5]="id p_s'";
	pars_tabl[11][5]=" ";
	pars_tabl[12][5]="id v'";
	pars_tabl[13][5]=" ";
	pars_tabl[14][5]="id st' m30";
	pars_tabl[15][5]=" ";
	pars_tabl[16][5]="st st_l'";
	pars_tabl[17][5]=" ";
	pars_tabl[18][5]="st_l";
	pars_tabl[19][5]=" ";
	pars_tabl[20][5]="id_l : m5 tp pr_l'";
	pars_tabl[21][5]=" ";
	pars_tabl[22][5]=" ";
	pars_tabl[23][5]=" ";
	pars_tabl[24][5]=" ";
	pars_tabl[25][5]=" ";
	pars_tabl[26][5]=" ";
	pars_tabl[27][5]=" ";
	pars_tabl[28][5]=" ";
	pars_tabl[29][5]=" ";
	pars_tabl[30][5]=" ";
	pars_tabl[31][5]="id m31 id_l'";
	pars_tabl[32][5]=" ";
	pars_tabl[33][5]=" ";
	pars_tabl[34][5]=" ";
	pars_tabl[35][5]=" ";
	pars_tabl[36][5]=" ";
	pars_tabl[37][5]=" ";
	pars_tabl[38][5]=" ";
	pars_tabl[39][5]=" ";
	pars_tabl[40][5]=" ";

// '{'
	pars_tabl[0][6]=" ";
	pars_tabl[1][6]=" ";
	pars_tabl[2][6]=" ";
	pars_tabl[3][6]=" ";
	pars_tabl[4][6]=" ";
	pars_tabl[5][6]=" ";
	pars_tabl[6][6]=" ";
	pars_tabl[7][6]=" ";
	pars_tabl[8][6]=" ";
	pars_tabl[9][6]=" ";
	pars_tabl[10][6]=" ";
	pars_tabl[11][6]=" ";
	pars_tabl[12][6]=" ";
	pars_tabl[13][6]=" ";
	pars_tabl[14][6]="c_s";
	pars_tabl[15][6]=" ";
	pars_tabl[16][6]="st st_l'";
	pars_tabl[17][6]=" ";
	pars_tabl[18][6]="st_l";
	pars_tabl[19][6]="{ op_s }";
	pars_tabl[20][6]=" ";
	pars_tabl[21][6]=" ";
	pars_tabl[22][6]=" ";
	pars_tabl[23][6]=" ";
	pars_tabl[24][6]=" ";
	pars_tabl[25][6]="0";
	pars_tabl[26][6]="0";
	pars_tabl[27][6]=" ";
	pars_tabl[28][6]=" ";
	pars_tabl[29][6]="0";
	pars_tabl[30][6]="0";
	pars_tabl[31][6]=" ";
	pars_tabl[32][6]=" ";
	pars_tabl[33][6]=" ";
	pars_tabl[34][6]=" ";
	pars_tabl[35][6]=" ";
	pars_tabl[36][6]=" ";
	pars_tabl[37][6]=" ";
	pars_tabl[38][6]=" ";
	pars_tabl[39][6]=" ";
	pars_tabl[40][6]=" ";


// '['
	pars_tabl[0][7]=" ";
	pars_tabl[1][7]=" ";
	pars_tabl[2][7]=" ";
	pars_tabl[3][7]=" ";
	pars_tabl[4][7]=" ";
	pars_tabl[5][7]=" ";
	pars_tabl[6][7]=" ";
	pars_tabl[7][7]=" ";
	pars_tabl[8][7]=" ";
	pars_tabl[9][7]=" ";
	pars_tabl[10][7]=" ";
	pars_tabl[11][7]=" ";
	pars_tabl[12][7]=" ";
	pars_tabl[13][7]="[ e ]";
	pars_tabl[14][7]=" ";
	pars_tabl[15][7]="v' as e m1";
	pars_tabl[16][7]=" ";
	pars_tabl[17][7]=" ";
	pars_tabl[18][7]=" ";
	pars_tabl[19][7]=" ";
	pars_tabl[20][7]=" ";
	pars_tabl[21][7]=" ";
	pars_tabl[22][7]=" ";
	pars_tabl[23][7]=" ";
	pars_tabl[24][7]=" ";
	pars_tabl[25][7]=" ";
	pars_tabl[26][7]=" ";
	pars_tabl[27][7]=" ";
	pars_tabl[28][7]=" ";
	pars_tabl[29][7]=" ";
	pars_tabl[30][7]=" ";
	pars_tabl[31][7]=" ";
	pars_tabl[32][7]=" ";
	pars_tabl[33][7]=" ";
	pars_tabl[34][7]=" ";
	pars_tabl[35][7]=" ";
	pars_tabl[36][7]=" ";
	pars_tabl[37][7]=" ";
	pars_tabl[38][7]=" ";
	pars_tabl[39][7]=" ";
	pars_tabl[40][7]=" ";

// ']'
	pars_tabl[0][8]=" ";
	pars_tabl[1][8]="0";
	pars_tabl[2][8]=" ";
	pars_tabl[3][8]="0";
	pars_tabl[4][8]=" ";
	pars_tabl[5][8]="0";
	pars_tabl[6][8]=" ";
	pars_tabl[7][8]="0";
	pars_tabl[8][8]=" ";
	pars_tabl[9][8]=" ";
	pars_tabl[10][8]=" ";
	pars_tabl[11][8]=" ";
	pars_tabl[12][8]=" ";
	pars_tabl[13][8]=" ";
	pars_tabl[14][8]=" ";
	pars_tabl[15][8]=" ";
	pars_tabl[16][8]=" ";
	pars_tabl[17][8]=" ";
	pars_tabl[18][8]=" ";
	pars_tabl[19][8]=" ";
	pars_tabl[20][8]=" ";
	pars_tabl[21][8]=" ";
	pars_tabl[22][8]=" ";
	pars_tabl[23][8]=" ";
	pars_tabl[24][8]=" ";
	pars_tabl[25][8]=" ";
	pars_tabl[26][8]=" ";
	pars_tabl[27][8]=" ";
	pars_tabl[28][8]=" ";
	pars_tabl[29][8]=" ";
	pars_tabl[30][8]=" ";
	pars_tabl[31][8]=" ";
	pars_tabl[32][8]=" ";
	pars_tabl[33][8]=" ";
	pars_tabl[34][8]=" ";
	pars_tabl[35][8]=" ";
	pars_tabl[36][8]=" ";
	pars_tabl[37][8]=" ";
	pars_tabl[38][8]=" ";
	pars_tabl[39][8]=" ";
	pars_tabl[40][8]=" ";

// '}'
	pars_tabl[0][9]=" ";
	pars_tabl[1][9]="0";
	pars_tabl[2][9]=" ";
	pars_tabl[3][9]="0";
	pars_tabl[4][9]=" ";
	pars_tabl[5][9]="0";
	pars_tabl[6][9]=" ";
	pars_tabl[7][9]="0";
	pars_tabl[8][9]=" ";
	pars_tabl[9][9]="0";
	pars_tabl[10][9]=" ";
	pars_tabl[11][9]="0";
	pars_tabl[12][9]=" ";
	pars_tabl[13][9]=" ";
	pars_tabl[14][9]=" ";
	pars_tabl[15][9]="0";//m23
	pars_tabl[16][9]=" ";
	pars_tabl[17][9]="0";
	pars_tabl[18][9]="0";
	pars_tabl[19][9]=" ";
	pars_tabl[20][9]=" ";
	pars_tabl[21][9]=" ";
	pars_tabl[22][9]=" ";
	pars_tabl[23][9]=" ";
	pars_tabl[24][9]=" ";
	pars_tabl[25][9]=" ";
	pars_tabl[26][9]=" ";
	pars_tabl[27][9]=" ";
	pars_tabl[28][9]=" ";
	pars_tabl[29][9]=" ";
	pars_tabl[30][9]=" ";
	pars_tabl[31][9]=" ";
	pars_tabl[32][9]="0";
	pars_tabl[33][9]=" ";
	pars_tabl[34][9]=" ";
	pars_tabl[35][9]=" ";
	pars_tabl[36][9]=" ";
	pars_tabl[37][9]=" ";
	pars_tabl[38][9]=" ";
	pars_tabl[39][9]=" ";
	pars_tabl[40][9]=" ";

// while
	pars_tabl[0][10]=" ";
	pars_tabl[1][10]=" ";
	pars_tabl[2][10]=" ";
	pars_tabl[3][10]=" ";
	pars_tabl[4][10]=" ";
	pars_tabl[5][10]=" ";
	pars_tabl[6][10]=" ";
	pars_tabl[7][10]=" ";
	pars_tabl[8][10]=" ";
	pars_tabl[9][10]=" ";
	pars_tabl[10][10]=" ";
	pars_tabl[11][10]=" ";
	pars_tabl[12][10]=" ";
	pars_tabl[13][10]=" ";
	pars_tabl[14][10]="while m19 e m13 do st m20 m14";
	pars_tabl[15][10]=" ";
	pars_tabl[16][10]="st st_l'";
	pars_tabl[17][10]=" ";
	pars_tabl[18][10]="st_l";
	pars_tabl[19][10]=" ";
	pars_tabl[20][10]=" ";
	pars_tabl[21][10]=" ";
	pars_tabl[22][10]=" ";
	pars_tabl[23][10]=" ";
	pars_tabl[24][10]=" ";
	pars_tabl[25][10]=" ";
	pars_tabl[26][10]=" ";
	pars_tabl[27][10]=" ";
	pars_tabl[28][10]=" ";
	pars_tabl[29][10]=" ";
	pars_tabl[30][10]=" ";
	pars_tabl[31][10]=" ";
	pars_tabl[32][10]=" ";
	pars_tabl[33][10]=" ";
	pars_tabl[34][10]=" ";
	pars_tabl[35][10]=" ";
	pars_tabl[36][10]=" ";
	pars_tabl[37][10]=" ";
	pars_tabl[38][10]=" ";
	pars_tabl[39][10]=" ";
	pars_tabl[40][10]=" ";
// do

	pars_tabl[0][11]=" ";
	pars_tabl[1][11]="0";
	pars_tabl[2][11]=" ";
	pars_tabl[3][11]="0";
	pars_tabl[4][11]=" ";
	pars_tabl[5][11]="0";
	pars_tabl[6][11]=" ";
	pars_tabl[7][11]="0";
	pars_tabl[8][11]=" ";
	pars_tabl[9][11]=" ";
	pars_tabl[10][11]=" ";
	pars_tabl[11][11]=" ";
	pars_tabl[12][11]=" ";
	pars_tabl[13][11]=" ";
	pars_tabl[14][11]=" ";
	pars_tabl[15][11]=" ";
	pars_tabl[16][11]=" ";
	pars_tabl[17][11]=" ";
	pars_tabl[18][11]=" ";
	pars_tabl[19][11]=" ";
	pars_tabl[20][11]=" ";
	pars_tabl[21][11]=" ";
	pars_tabl[22][11]=" ";
	pars_tabl[23][11]=" ";
	pars_tabl[24][11]=" ";
	pars_tabl[25][11]=" ";
	pars_tabl[26][11]=" ";
	pars_tabl[27][11]=" ";
	pars_tabl[28][11]=" ";
	pars_tabl[29][11]=" ";
	pars_tabl[30][11]=" ";
	pars_tabl[31][11]=" ";
	pars_tabl[32][11]=" ";
	pars_tabl[33][11]=" ";
	pars_tabl[34][11]=" ";
	pars_tabl[35][11]=" ";
	pars_tabl[36][11]=" ";
	pars_tabl[37][11]=" ";
	pars_tabl[38][11]=" ";
	pars_tabl[39][11]=" ";
	pars_tabl[40][11]=" ";

//if 
	pars_tabl[0][12]=" ";
	pars_tabl[1][12]=" ";
	pars_tabl[2][12]=" ";
	pars_tabl[3][12]=" ";
	pars_tabl[4][12]=" ";
	pars_tabl[5][12]=" ";
	pars_tabl[6][12]=" ";
	pars_tabl[7][12]=" ";
	pars_tabl[8][12]=" ";
	pars_tabl[9][12]=" ";
	pars_tabl[10][12]=" ";
	pars_tabl[11][12]=" ";
	pars_tabl[12][12]=" ";
	pars_tabl[13][12]=" ";
	pars_tabl[14][12]="if e m13 then st m15 else m14 st m16";
	pars_tabl[15][12]=" ";
	pars_tabl[16][12]="st st_l'";
	pars_tabl[17][12]=" ";
	pars_tabl[18][12]="st_l";
	pars_tabl[19][12]=" ";
	pars_tabl[20][12]=" ";
	pars_tabl[21][12]=" ";
	pars_tabl[22][12]=" ";
	pars_tabl[23][12]=" ";
	pars_tabl[24][12]=" ";
	pars_tabl[25][12]=" ";
	pars_tabl[26][12]=" ";
	pars_tabl[27][12]=" ";
	pars_tabl[28][12]=" ";
	pars_tabl[29][12]=" ";
	pars_tabl[30][12]=" ";
	pars_tabl[31][12]=" ";
	pars_tabl[32][12]=" ";
	pars_tabl[33][12]=" ";
	pars_tabl[34][12]=" ";
	pars_tabl[35][12]=" ";
	pars_tabl[36][12]=" ";
	pars_tabl[37][12]=" ";
	pars_tabl[38][12]=" ";
	pars_tabl[39][12]=" ";
	pars_tabl[40][12]=" ";

// else
	pars_tabl[0][13]=" ";
	pars_tabl[1][13]="0";
	pars_tabl[2][13]=" ";
	pars_tabl[3][13]="0";
	pars_tabl[4][13]=" ";
	pars_tabl[5][13]="0";
	pars_tabl[6][13]=" ";
	pars_tabl[7][13]="0";
	pars_tabl[8][13]=" ";
	pars_tabl[9][13]="0";
	pars_tabl[10][13]=" ";
	pars_tabl[11][13]="0";
	pars_tabl[12][13]=" ";
	pars_tabl[13][13]=" ";
	pars_tabl[14][13]=" ";
	pars_tabl[15][13]="0";//m23
	pars_tabl[16][13]=" ";
	pars_tabl[17][13]=" ";
	pars_tabl[18][13]=" ";
	pars_tabl[19][13]=" ";
	pars_tabl[20][13]=" ";
	pars_tabl[21][13]=" ";
	pars_tabl[22][13]=" ";
	pars_tabl[23][13]=" ";
	pars_tabl[24][13]=" ";
	pars_tabl[25][13]=" ";
	pars_tabl[26][13]=" ";
	pars_tabl[27][13]=" ";
	pars_tabl[28][13]=" ";
	pars_tabl[29][13]=" ";
	pars_tabl[30][13]=" ";
	pars_tabl[31][13]=" ";
	pars_tabl[32][13]="0";
	pars_tabl[33][13]=" ";
	pars_tabl[34][13]=" ";
	pars_tabl[35][13]=" ";
	pars_tabl[36][13]=" ";
	pars_tabl[37][13]=" ";
	pars_tabl[38][13]=" ";
	pars_tabl[39][13]=" ";
	pars_tabl[40][13]=" ";
// then
	pars_tabl[0][14]=" ";
	pars_tabl[1][14]="0";
	pars_tabl[2][14]=" ";
	pars_tabl[3][14]="0";
	pars_tabl[4][14]=" ";
	pars_tabl[5][14]="0";
	pars_tabl[6][14]=" ";
	pars_tabl[7][14]="0";
	pars_tabl[8][14]=" ";
	pars_tabl[9][14]=" ";
	pars_tabl[10][14]=" ";
	pars_tabl[11][14]=" ";
	pars_tabl[12][14]=" ";
	pars_tabl[13][14]=" ";
	pars_tabl[14][14]=" ";
	pars_tabl[15][14]=" ";
	pars_tabl[16][14]=" ";
	pars_tabl[17][14]=" ";
	pars_tabl[18][14]=" ";
	pars_tabl[19][14]=" ";
	pars_tabl[20][14]=" ";
	pars_tabl[21][14]=" ";
	pars_tabl[22][14]=" ";
	pars_tabl[23][14]=" ";
	pars_tabl[24][14]=" ";
	pars_tabl[25][14]=" ";
	pars_tabl[26][14]=" ";
	pars_tabl[27][14]=" ";
	pars_tabl[28][14]=" ";
	pars_tabl[29][14]=" ";
	pars_tabl[30][14]=" ";
	pars_tabl[31][14]=" ";
	pars_tabl[32][14]=" ";
	pars_tabl[33][14]=" ";
	pars_tabl[34][14]=" ";
	pars_tabl[35][14]=" ";
	pars_tabl[36][14]=" ";
	pars_tabl[37][14]=" ";
	pars_tabl[38][14]=" ";
	pars_tabl[39][14]=" ";
	pars_tabl[40][14]=" ";

// :=
	pars_tabl[0][15]=" ";
	pars_tabl[1][15]=" ";
	pars_tabl[2][15]=" ";
	pars_tabl[3][15]=" ";
	pars_tabl[4][15]=" ";
	pars_tabl[5][15]=" ";
	pars_tabl[6][15]=" ";
	pars_tabl[7][15]=" ";
	pars_tabl[8][15]=" ";
	pars_tabl[9][15]=" ";
	pars_tabl[10][15]=" ";
	pars_tabl[11][15]=" ";
	pars_tabl[12][15]=" ";
	pars_tabl[13][15]="0";
	pars_tabl[14][15]=" ";
	pars_tabl[15][15]="v' as e m1";
	pars_tabl[16][15]=" ";
	pars_tabl[17][15]=" ";
	pars_tabl[18][15]=" ";
	pars_tabl[19][15]=" ";
	pars_tabl[20][15]=" ";
	pars_tabl[21][15]=" ";
	pars_tabl[22][15]=" ";
	pars_tabl[23][15]=" ";
	pars_tabl[24][15]=" ";
	pars_tabl[25][15]=" ";
	pars_tabl[26][15]=" ";
	pars_tabl[27][15]=" ";
	pars_tabl[28][15]=" ";
	pars_tabl[29][15]=" ";
	pars_tabl[30][15]=" ";
	pars_tabl[31][15]=" ";
	pars_tabl[32][15]=" ";
	pars_tabl[33][15]=" ";
	pars_tabl[34][15]=" ";
	pars_tabl[35][15]=" ";
	pars_tabl[36][15]=":=";
	pars_tabl[37][15]=" ";
	pars_tabl[38][15]=" ";
	pars_tabl[39][15]=" ";
	pars_tabl[40][15]=" ";

// function
	pars_tabl[0][16]=" ";
	pars_tabl[1][16]=" ";
	pars_tabl[2][16]=" ";
	pars_tabl[3][16]=" ";
	pars_tabl[4][16]=" ";
	pars_tabl[5][16]=" ";
	pars_tabl[6][16]=" ";
	pars_tabl[7][16]=" ";
	pars_tabl[8][16]=" ";
	pars_tabl[9][16]=" ";
	pars_tabl[10][16]=" ";
	pars_tabl[11][16]=" ";
	pars_tabl[12][16]=" ";
	pars_tabl[13][16]=" ";
	pars_tabl[14][16]=" ";
	pars_tabl[15][16]=" ";
	pars_tabl[16][16]=" ";
	pars_tabl[17][16]=" ";
	pars_tabl[18][16]=" ";
	pars_tabl[19][16]=" ";
	pars_tabl[20][16]=" ";
	pars_tabl[21][16]=" ";
	pars_tabl[22][16]=" ";
	pars_tabl[23][16]="function id m17 ar  : st_tp ;";
	pars_tabl[24][16]="sub_h m8 dec m7 c_s m18";
	pars_tabl[25][16]="sub_decs'";
	pars_tabl[26][16]="sub_dec sub_decs'";
	pars_tabl[27][16]=" ";
	pars_tabl[28][16]=" ";
	pars_tabl[29][16]="0";
	pars_tabl[30][16]="0";
	pars_tabl[31][16]=" ";
	pars_tabl[32][16]=" ";
	pars_tabl[33][16]=" ";
	pars_tabl[34][16]=" ";
	pars_tabl[35][16]=" ";
	pars_tabl[36][16]=" ";
	pars_tabl[37][16]=" ";
	pars_tabl[38][16]=" ";
	pars_tabl[39][16]=" ";
	pars_tabl[40][16]=" ";

// procedure
	pars_tabl[0][17]=" ";
	pars_tabl[1][17]=" ";
	pars_tabl[2][17]=" ";
	pars_tabl[3][17]=" ";
	pars_tabl[4][17]=" ";
	pars_tabl[5][17]=" ";
	pars_tabl[6][17]=" ";
	pars_tabl[7][17]=" ";
	pars_tabl[8][17]=" ";
	pars_tabl[9][17]=" ";
	pars_tabl[10][17]=" ";
	pars_tabl[11][17]=" ";
	pars_tabl[12][17]=" ";
	pars_tabl[13][17]=" ";
	pars_tabl[14][17]=" ";
	pars_tabl[15][17]=" ";
	pars_tabl[16][17]=" ";
	pars_tabl[17][17]=" ";
	pars_tabl[18][17]=" ";
	pars_tabl[19][17]=" ";
	pars_tabl[20][17]=" ";
	pars_tabl[21][17]=" ";
	pars_tabl[22][17]=" ";
	pars_tabl[23][17]="procedure id m17 ar ;";
	pars_tabl[24][17]="sub_h m8 dec m7 c_s m18";
	pars_tabl[25][17]="sub_decs'";
	pars_tabl[26][17]="sub_dec sub_decs'";
	pars_tabl[27][17]=" ";
	pars_tabl[28][17]=" ";
	pars_tabl[29][17]="0";
	pars_tabl[30][17]="0";
	pars_tabl[31][17]=" ";
	pars_tabl[32][17]=" ";
	pars_tabl[33][17]=" ";
	pars_tabl[34][17]=" ";
	pars_tabl[35][17]=" ";
	pars_tabl[36][17]=" ";
	pars_tabl[37][17]=" ";
	pars_tabl[38][17]=" ";
	pars_tabl[39][17]=" ";
	pars_tabl[40][17]=" ";
// integre

	pars_tabl[0][18]=" ";
	pars_tabl[1][18]=" ";
	pars_tabl[2][18]=" ";
	pars_tabl[3][18]=" ";
	pars_tabl[4][18]=" ";
	pars_tabl[5][18]=" ";
	pars_tabl[6][18]=" ";
	pars_tabl[7][18]=" ";
	pars_tabl[8][18]=" ";
	pars_tabl[9][18]=" ";
	pars_tabl[10][18]=" ";
	pars_tabl[11][18]=" ";
	pars_tabl[12][18]=" ";
	pars_tabl[13][18]=" ";
	pars_tabl[14][18]=" ";
	pars_tabl[15][18]=" ";
	pars_tabl[16][18]=" ";
	pars_tabl[17][18]=" ";
	pars_tabl[18][18]=" ";
	pars_tabl[19][18]=" ";
	pars_tabl[20][18]=" ";
	pars_tabl[21][18]=" ";
	pars_tabl[22][18]=" ";
	pars_tabl[23][18]=" ";
	pars_tabl[24][18]=" ";
	pars_tabl[25][18]=" ";
	pars_tabl[26][18]=" ";
	pars_tabl[27][18]="integer";
	pars_tabl[28][18]="st_tp ";
	pars_tabl[29][18]=" ";
	pars_tabl[30][18]=" ";
	pars_tabl[31][18]=" ";
	pars_tabl[32][18]=" ";
	pars_tabl[33][18]=" ";
	pars_tabl[34][18]=" ";
	pars_tabl[35][18]=" ";
	pars_tabl[36][18]=" ";
	pars_tabl[37][18]=" ";
	pars_tabl[38][18]=" ";
	pars_tabl[39][18]=" ";
	pars_tabl[40][18]=" ";

// real
	pars_tabl[0][19]=" ";
	pars_tabl[1][19]=" ";
	pars_tabl[2][19]=" ";
	pars_tabl[3][19]=" ";
	pars_tabl[4][19]=" ";
	pars_tabl[5][19]=" ";
	pars_tabl[6][19]=" ";
	pars_tabl[7][19]=" ";
	pars_tabl[8][19]=" ";
	pars_tabl[9][19]=" ";
	pars_tabl[10][19]=" ";
	pars_tabl[11][19]=" ";
	pars_tabl[12][19]=" ";
	pars_tabl[13][19]=" ";
	pars_tabl[14][19]=" ";
	pars_tabl[15][19]=" ";
	pars_tabl[16][19]=" ";
	pars_tabl[17][19]=" ";
	pars_tabl[18][19]=" ";
	pars_tabl[19][19]=" ";
	pars_tabl[20][19]=" ";
	pars_tabl[21][19]=" ";
	pars_tabl[22][19]=" ";
	pars_tabl[23][19]=" ";
	pars_tabl[24][19]=" ";
	pars_tabl[25][19]=" ";
	pars_tabl[26][19]=" ";
	pars_tabl[27][19]="real";
	pars_tabl[28][19]="st_tp";
	pars_tabl[29][19]=" ";
	pars_tabl[30][19]=" ";
	pars_tabl[31][19]=" ";
	pars_tabl[32][19]=" ";
	pars_tabl[33][19]=" ";
	pars_tabl[34][19]=" ";
	pars_tabl[35][19]=" ";
	pars_tabl[36][19]=" ";
	pars_tabl[37][19]=" ";
	pars_tabl[38][19]=" ";
	pars_tabl[39][19]=" ";
	pars_tabl[40][19]=" ";

// array
	// arrary
	pars_tabl[0][20]=" ";
	pars_tabl[1][20]=" ";
	pars_tabl[2][20]=" ";
	pars_tabl[3][20]=" ";
	pars_tabl[4][20]=" ";
	pars_tabl[5][20]=" ";
	pars_tabl[6][20]=" ";
	pars_tabl[7][20]=" ";
	pars_tabl[8][20]=" ";
	pars_tabl[9][20]=" ";
	pars_tabl[10][20]=" ";
	pars_tabl[11][20]=" ";
	pars_tabl[12][20]=" ";
	pars_tabl[13][20]=" ";
	pars_tabl[14][20]=" ";
	pars_tabl[15][20]=" ";
	pars_tabl[16][20]=" ";
	pars_tabl[17][20]=" ";
	pars_tabl[18][20]=" ";
	pars_tabl[19][20]=" ";
	pars_tabl[20][20]=" ";
	pars_tabl[21][20]=" ";
	pars_tabl[22][20]=" ";
	pars_tabl[23][20]=" ";
	pars_tabl[24][20]=" ";
	pars_tabl[25][20]=" ";
	pars_tabl[26][20]=" ";
	pars_tabl[27][20]=" ";
	pars_tabl[28][20]="array [ num .. num ] of tp";
	pars_tabl[29][20]=" ";
	pars_tabl[30][20]=" ";
	pars_tabl[31][20]=" ";
	pars_tabl[32][20]=" ";
	pars_tabl[33][20]=" ";
	pars_tabl[34][20]=" ";
	pars_tabl[35][20]=" ";
	pars_tabl[36][20]=" ";
	pars_tabl[37][20]=" ";
	pars_tabl[38][20]=" ";
	pars_tabl[39][20]=" ";
	pars_tabl[40][20]=" ";
//of
	pars_tabl[0][21]=" ";
	pars_tabl[1][21]=" ";
	pars_tabl[2][21]=" ";
	pars_tabl[3][21]=" ";
	pars_tabl[4][21]=" ";
	pars_tabl[5][21]=" ";
	pars_tabl[6][21]=" ";
	pars_tabl[7][21]=" ";
	pars_tabl[8][21]=" ";
	pars_tabl[9][21]=" ";
	pars_tabl[10][21]=" ";
	pars_tabl[11][21]=" ";
	pars_tabl[12][21]=" ";
	pars_tabl[13][21]=" ";
	pars_tabl[14][21]=" ";
	pars_tabl[15][21]=" ";
	pars_tabl[16][21]=" ";
	pars_tabl[17][21]=" ";
	pars_tabl[18][21]=" ";
	pars_tabl[19][21]=" ";
	pars_tabl[20][21]=" ";
	pars_tabl[21][21]=" ";
	pars_tabl[22][21]=" ";
	pars_tabl[23][21]=" ";
	pars_tabl[24][21]=" ";
	pars_tabl[25][21]=" ";
	pars_tabl[26][21]=" ";
	pars_tabl[27][21]=" ";
	pars_tabl[28][21]=" ";
	pars_tabl[29][21]=" ";
	pars_tabl[30][21]=" ";
	pars_tabl[31][21]=" ";
	pars_tabl[32][21]=" ";
	pars_tabl[33][21]=" ";
	pars_tabl[34][21]=" ";
	pars_tabl[35][21]=" ";
	pars_tabl[36][21]=" ";
	pars_tabl[37][21]=" ";
	pars_tabl[38][21]=" ";
	pars_tabl[39][21]=" ";
	pars_tabl[40][21]=" ";
// var

	pars_tabl[0][22]=" ";
	pars_tabl[1][22]=" ";
	pars_tabl[2][22]=" ";
	pars_tabl[3][22]=" ";
	pars_tabl[4][22]=" ";
	pars_tabl[5][22]=" ";
	pars_tabl[6][22]=" ";
	pars_tabl[7][22]=" ";
	pars_tabl[8][22]=" ";
	pars_tabl[9][22]=" ";
	pars_tabl[10][22]=" ";
	pars_tabl[11][22]=" ";
	pars_tabl[12][22]=" ";
	pars_tabl[13][22]=" ";
	pars_tabl[14][22]=" ";
	pars_tabl[15][22]=" ";
	pars_tabl[16][22]=" ";
	pars_tabl[17][22]=" ";
	pars_tabl[18][22]=" ";
	pars_tabl[19][22]=" ";
	pars_tabl[20][22]=" ";
	pars_tabl[21][22]=" ";
	pars_tabl[22][22]=" ";
	pars_tabl[23][22]=" ";
	pars_tabl[24][22]=" ";
	pars_tabl[25][22]=" ";
	pars_tabl[26][22]=" ";
	pars_tabl[27][22]=" ";
	pars_tabl[28][22]=" ";
	pars_tabl[29][22]="dec'";
	pars_tabl[30][22]="m4 var id_l : m3 tp ; dec'";
	pars_tabl[31][22]=" ";
	pars_tabl[32][22]=" ";
	pars_tabl[33][22]=" ";
	pars_tabl[34][22]=" ";
	pars_tabl[35][22]=" ";
	pars_tabl[36][22]=" ";
	pars_tabl[37][22]=" ";
	pars_tabl[38][22]=" ";
	pars_tabl[39][22]=" ";
	pars_tabl[40][22]=" ";
//progrm

	pars_tabl[0][23]=" ";
	pars_tabl[1][23]=" ";
	pars_tabl[2][23]=" ";
	pars_tabl[3][23]=" ";
	pars_tabl[4][23]=" ";
	pars_tabl[5][23]=" ";
	pars_tabl[6][23]=" ";
	pars_tabl[7][23]=" ";
	pars_tabl[8][23]=" ";
	pars_tabl[9][23]=" ";
	pars_tabl[10][23]=" ";
	pars_tabl[11][23]=" ";
	pars_tabl[12][23]=" ";
	pars_tabl[13][23]=" ";
	pars_tabl[14][23]=" ";
	pars_tabl[15][23]=" ";
	pars_tabl[16][23]=" ";
	pars_tabl[17][23]=" ";
	pars_tabl[18][23]=" ";
	pars_tabl[19][23]=" ";
	pars_tabl[20][23]=" ";
	pars_tabl[21][23]=" ";
	pars_tabl[22][23]=" ";
	pars_tabl[23][23]=" ";
	pars_tabl[24][23]=" ";
	pars_tabl[25][23]=" ";
	pars_tabl[26][23]=" ";
	pars_tabl[27][23]=" ";
	pars_tabl[28][23]=" ";
	pars_tabl[29][23]=" ";
	pars_tabl[30][23]=" ";
	pars_tabl[31][23]=" ";
	pars_tabl[32][23]=" ";
	pars_tabl[33][23]="program id ( id_l ) ; m24 dec sub_decs m25 m7 c_s m28";//m28
	pars_tabl[34][23]=" ";
	pars_tabl[35][23]=" ";
	pars_tabl[36][23]=" ";
	pars_tabl[37][23]=" ";
	pars_tabl[38][23]=" ";
	pars_tabl[39][23]=" ";
	pars_tabl[40][23]=" ";


// ;
	pars_tabl[0][24]=" ";
	pars_tabl[1][24]="0";
	pars_tabl[2][24]=" ";
	pars_tabl[3][24]="0";
	pars_tabl[4][24]=" ";
	pars_tabl[5][24]="0";
	pars_tabl[6][24]=" ";
	pars_tabl[7][24]="0";
	pars_tabl[8][24]=" ";
	pars_tabl[9][24]="0";
	pars_tabl[10][24]=" ";
	pars_tabl[11][24]="0";
	pars_tabl[12][24]=" ";
	pars_tabl[13][24]=" ";
	pars_tabl[14][24]=" ";
	pars_tabl[15][24]="0";//m23
	pars_tabl[16][24]=" ";
	pars_tabl[17][24]="; st st_l'";
	pars_tabl[18][24]=" ";
	pars_tabl[19][24]=" ";
	pars_tabl[20][24]=" ";
	pars_tabl[21][24]="m4 ; id_l : m5 tp pr_l'";
	pars_tabl[22][24]="0";
	pars_tabl[23][24]=" ";
	pars_tabl[24][24]=" ";
	pars_tabl[25][24]=" ";
	pars_tabl[26][24]=" ";
	pars_tabl[27][24]=" ";
	pars_tabl[28][24]=" ";
	pars_tabl[29][24]=" ";
	pars_tabl[30][24]=" ";
	pars_tabl[31][24]=" ";
	pars_tabl[32][24]="0";
	pars_tabl[33][24]=" ";
	pars_tabl[34][24]=" ";
	pars_tabl[35][24]=" ";
	pars_tabl[36][24]=" ";
	pars_tabl[37][24]=" ";
	pars_tabl[38][24]=" ";
	pars_tabl[39][24]=" ";
	pars_tabl[40][24]=" ";
// :
	pars_tabl[0][25]=" ";
	pars_tabl[1][25]=" ";
	pars_tabl[2][25]=" ";
	pars_tabl[3][25]=" ";
	pars_tabl[4][25]=" ";
	pars_tabl[5][25]=" ";
	pars_tabl[6][25]=" ";
	pars_tabl[7][25]=" ";
	pars_tabl[8][25]=" ";
	pars_tabl[9][25]=" ";
	pars_tabl[10][25]=" ";
	pars_tabl[11][25]=" ";
	pars_tabl[12][25]=" ";
	pars_tabl[13][25]=" ";
	pars_tabl[14][25]=" ";
	pars_tabl[15][25]=" ";
	pars_tabl[16][25]=" ";
	pars_tabl[17][25]=" ";
	pars_tabl[18][25]=" ";
	pars_tabl[19][25]=" ";
	pars_tabl[20][25]=" ";
	pars_tabl[21][25]=" ";
	pars_tabl[22][25]="0";
	pars_tabl[23][25]=" ";
	pars_tabl[24][25]=" ";
	pars_tabl[25][25]=" ";
	pars_tabl[26][25]=" ";
	pars_tabl[27][25]=" ";
	pars_tabl[28][25]=" ";
	pars_tabl[29][25]=" ";
	pars_tabl[30][25]=" ";
	pars_tabl[31][25]=" ";
	pars_tabl[32][25]="0";
	pars_tabl[33][25]=" ";
	pars_tabl[34][25]=" ";
	pars_tabl[35][25]=" ";
	pars_tabl[36][25]=" ";
	pars_tabl[37][25]=" ";
	pars_tabl[38][25]=" ";
	pars_tabl[39][25]=" ";
	pars_tabl[40][25]=" ";
// ,

	pars_tabl[0][26]=" ";
	pars_tabl[1][26]="0";
	pars_tabl[2][26]=" ";
	pars_tabl[3][26]="0";
	pars_tabl[4][26]=" ";
	pars_tabl[5][26]="0";
	pars_tabl[6][26]=" ";
	pars_tabl[7][26]="0";
	pars_tabl[8][26]=" ";
	pars_tabl[9][26]=", e e_l'";
	pars_tabl[10][26]=" ";
	pars_tabl[11][26]=" ";
	pars_tabl[12][26]=" ";
	pars_tabl[13][26]=" ";
	pars_tabl[14][26]=" ";
	pars_tabl[15][26]=" ";
	pars_tabl[16][26]=" ";
	pars_tabl[17][26]=" ";
	pars_tabl[18][26]=" ";
	pars_tabl[19][26]=" ";
	pars_tabl[20][26]=" ";
	pars_tabl[21][26]=" ";
	pars_tabl[22][26]=" ";
	pars_tabl[23][26]=" ";
	pars_tabl[24][26]=" ";
	pars_tabl[25][26]=" ";
	pars_tabl[26][26]=" ";
	pars_tabl[27][26]=" ";
	pars_tabl[28][26]=" ";
	pars_tabl[29][26]=" ";
	pars_tabl[30][26]=" ";
	pars_tabl[31][26]=" ";
	pars_tabl[32][26]=", id m31 id_l'";
	pars_tabl[33][26]=" ";
	pars_tabl[34][26]=" ";
	pars_tabl[35][26]=" ";
	pars_tabl[36][26]=" ";
	pars_tabl[37][26]=" ";
	pars_tabl[38][26]=" ";
	pars_tabl[39][26]=" ";
	pars_tabl[40][26]=" ";

// int_num
	pars_tabl[0][27]="num";
	pars_tabl[1][27]=" ";
	pars_tabl[2][27]="f t'";
	pars_tabl[3][27]=" ";
	pars_tabl[4][27]="t s_e'";
	pars_tabl[5][27]=" ";
	pars_tabl[6][27]="s_e e'";
	pars_tabl[7][27]=" ";
	pars_tabl[8][27]="e e_l'";
	pars_tabl[9][27]=" ";
	pars_tabl[10][27]=" ";
	pars_tabl[11][27]=" ";
	pars_tabl[12][27]=" ";
	pars_tabl[13][27]=" ";
	pars_tabl[14][27]=" ";
	pars_tabl[15][27]=" ";
	pars_tabl[16][27]=" ";
	pars_tabl[17][27]=" ";
	pars_tabl[18][27]=" ";
	pars_tabl[19][27]=" ";
	pars_tabl[20][27]=" ";
	pars_tabl[21][27]=" ";
	pars_tabl[22][27]=" ";
	pars_tabl[23][27]=" ";
	pars_tabl[24][27]=" ";
	pars_tabl[25][27]=" ";
	pars_tabl[26][27]=" ";
	pars_tabl[27][27]=" ";
	pars_tabl[28][27]=" ";
	pars_tabl[29][27]=" ";
	pars_tabl[30][27]=" ";
	pars_tabl[31][27]=" ";
	pars_tabl[32][27]=" ";
	pars_tabl[33][27]=" ";
	pars_tabl[34][27]=" ";
	pars_tabl[35][27]=" ";
	pars_tabl[36][27]=" ";
	pars_tabl[37][27]=" ";
	pars_tabl[38][27]=" ";
	pars_tabl[39][27]=" ";
	pars_tabl[40][27]="m21 int_num ";

// float_num
	pars_tabl[0][28]="num";
	pars_tabl[1][28]=" ";
	pars_tabl[2][28]="f t'";
	pars_tabl[3][28]=" ";
	pars_tabl[4][28]="t s_e'";
	pars_tabl[5][28]=" ";
	pars_tabl[6][28]="s_e e'";
	pars_tabl[7][28]=" ";
	pars_tabl[8][28]="e e_l'";
	pars_tabl[9][28]=" ";
	pars_tabl[10][28]=" ";
	pars_tabl[11][28]=" ";
	pars_tabl[12][28]=" ";
	pars_tabl[13][28]=" ";
	pars_tabl[14][28]=" ";
	pars_tabl[15][28]=" ";
	pars_tabl[16][28]=" ";
	pars_tabl[17][28]=" ";
	pars_tabl[18][28]=" ";
	pars_tabl[19][28]=" ";
	pars_tabl[20][28]=" ";
	pars_tabl[21][28]=" ";
	pars_tabl[22][28]=" ";
	pars_tabl[23][28]=" ";
	pars_tabl[24][28]=" ";
	pars_tabl[25][28]=" ";
	pars_tabl[26][28]=" ";
	pars_tabl[27][28]=" ";
	pars_tabl[28][28]=" ";
	pars_tabl[29][28]=" ";
	pars_tabl[30][28]=" ";
	pars_tabl[31][28]=" ";
	pars_tabl[32][28]=" ";
	pars_tabl[33][28]=" ";
	pars_tabl[34][28]=" ";
	pars_tabl[35][28]=" ";
	pars_tabl[36][28]=" ";
	pars_tabl[37][28]=" ";
	pars_tabl[38][28]=" ";
	pars_tabl[39][28]=" ";
	pars_tabl[40][28]="m22 float_num";

// or
	
	pars_tabl[0][29]=" ";
	pars_tabl[1][29]="0";
	pars_tabl[2][29]=" ";
	pars_tabl[3][29]="0";
	pars_tabl[4][29]=" ";
	pars_tabl[5][29]="ad t s_e' m2";
	pars_tabl[6][29]=" ";
	pars_tabl[7][29]=" ";
	pars_tabl[8][29]=" ";
	pars_tabl[9][29]=" ";
	pars_tabl[10][29]=" ";
	pars_tabl[11][29]=" ";
	pars_tabl[12][29]=" ";
	pars_tabl[13][29]=" ";
	pars_tabl[14][29]=" ";
	pars_tabl[15][29]=" ";
	pars_tabl[16][29]=" ";
	pars_tabl[17][29]=" ";
	pars_tabl[18][29]=" ";
	pars_tabl[19][29]=" ";
	pars_tabl[20][29]=" ";
	pars_tabl[21][29]=" ";
	pars_tabl[22][29]=" ";
	pars_tabl[23][29]=" ";
	pars_tabl[24][29]=" ";
	pars_tabl[25][29]=" ";
	pars_tabl[26][29]=" ";
	pars_tabl[27][29]=" ";
	pars_tabl[28][29]=" ";
	pars_tabl[29][29]=" ";
	pars_tabl[30][29]=" ";
	pars_tabl[31][29]=" ";
	pars_tabl[32][29]=" ";
	pars_tabl[33][29]=" ";
	pars_tabl[34][29]="or";
	pars_tabl[35][29]=" ";
	pars_tabl[36][29]=" ";
	pars_tabl[37][29]=" ";
	pars_tabl[38][29]=" ";
	pars_tabl[39][29]=" ";
	pars_tabl[40][29]=" ";

// *
	pars_tabl[0][30]=" ";
	pars_tabl[1][30]="0";
	pars_tabl[2][30]=" ";
	pars_tabl[3][30]="mulop f t' m9";
	pars_tabl[4][30]=" ";
	pars_tabl[5][30]=" ";
	pars_tabl[6][30]=" ";
	pars_tabl[7][30]=" ";
	pars_tabl[8][30]=" ";
	pars_tabl[9][30]=" ";
	pars_tabl[10][30]=" ";
	pars_tabl[11][30]=" ";
	pars_tabl[12][30]=" ";
	pars_tabl[13][30]=" ";
	pars_tabl[14][30]=" ";
	pars_tabl[15][30]=" ";
	pars_tabl[16][30]=" ";
	pars_tabl[17][30]=" ";
	pars_tabl[18][30]=" ";
	pars_tabl[19][30]=" ";
	pars_tabl[20][30]=" ";
	pars_tabl[21][30]=" ";
	pars_tabl[22][30]=" ";
	pars_tabl[23][30]=" ";
	pars_tabl[24][30]=" ";
	pars_tabl[25][30]=" ";
	pars_tabl[26][30]=" ";
	pars_tabl[27][30]=" ";
	pars_tabl[28][30]=" ";
	pars_tabl[29][30]=" ";
	pars_tabl[30][30]=" ";
	pars_tabl[31][30]=" ";
	pars_tabl[32][30]=" ";
	pars_tabl[33][30]=" ";
	pars_tabl[34][30]=" ";
	pars_tabl[35][30]="*";
	pars_tabl[36][30]=" ";
	pars_tabl[37][30]=" ";
	pars_tabl[38][30]=" ";
	pars_tabl[39][30]=" ";
	pars_tabl[40][30]=" ";


// '/'

	pars_tabl[0][31]=" ";
	pars_tabl[1][31]="0";
	pars_tabl[2][31]=" ";
	pars_tabl[3][31]="mulop f t' m9";
	pars_tabl[4][31]=" ";
	pars_tabl[5][31]=" ";
	pars_tabl[6][31]=" ";
	pars_tabl[7][31]=" ";
	pars_tabl[8][31]=" ";
	pars_tabl[9][31]=" ";
	pars_tabl[10][31]=" ";
	pars_tabl[11][31]=" ";
	pars_tabl[12][31]=" ";
	pars_tabl[13][31]=" ";
	pars_tabl[14][31]=" ";
	pars_tabl[15][31]=" ";
	pars_tabl[16][31]=" ";
	pars_tabl[17][31]=" ";
	pars_tabl[18][31]=" ";
	pars_tabl[19][31]=" ";
	pars_tabl[20][31]=" ";
	pars_tabl[21][31]=" ";
	pars_tabl[22][31]=" ";
	pars_tabl[23][31]=" ";
	pars_tabl[24][31]=" ";
	pars_tabl[25][31]=" ";
	pars_tabl[26][31]=" ";
	pars_tabl[27][31]=" ";
	pars_tabl[28][31]=" ";
	pars_tabl[29][31]=" ";
	pars_tabl[30][31]=" ";
	pars_tabl[31][31]=" ";
	pars_tabl[32][31]=" ";
	pars_tabl[33][31]=" ";
	pars_tabl[34][31]=" ";
	pars_tabl[35][31]="/";
	pars_tabl[36][31]=" ";
	pars_tabl[37][31]=" ";
	pars_tabl[38][31]=" ";
	pars_tabl[39][31]=" ";
	pars_tabl[40][31]=" ";


// and


	pars_tabl[0][32]=" ";
	pars_tabl[1][32]="0";
	pars_tabl[2][32]=" ";
	pars_tabl[3][32]="mulop f t' m9";
	pars_tabl[4][32]=" ";
	pars_tabl[5][32]=" ";
	pars_tabl[6][32]=" ";
	pars_tabl[7][32]=" ";
	pars_tabl[8][32]=" ";
	pars_tabl[9][32]=" ";
	pars_tabl[10][32]=" ";
	pars_tabl[11][32]=" ";
	pars_tabl[12][32]=" ";
	pars_tabl[13][32]=" ";
	pars_tabl[14][32]=" ";
	pars_tabl[15][32]=" ";
	pars_tabl[16][32]=" ";
	pars_tabl[17][32]=" ";
	pars_tabl[18][32]=" ";
	pars_tabl[19][32]=" ";
	pars_tabl[20][32]=" ";
	pars_tabl[21][32]=" ";
	pars_tabl[22][32]=" ";
	pars_tabl[23][32]=" ";
	pars_tabl[24][32]=" ";
	pars_tabl[25][32]=" ";
	pars_tabl[26][32]=" ";
	pars_tabl[27][32]=" ";
	pars_tabl[28][32]=" ";
	pars_tabl[29][32]=" ";
	pars_tabl[30][32]=" ";
	pars_tabl[31][32]=" ";
	pars_tabl[32][32]=" ";
	pars_tabl[33][32]=" ";
	pars_tabl[34][32]=" ";
	pars_tabl[35][32]="and";
	pars_tabl[36][32]=" ";
	pars_tabl[37][32]=" ";
	pars_tabl[38][32]=" ";
	pars_tabl[39][32]=" ";
	pars_tabl[40][32]=" ";
// mod
	pars_tabl[0][33]=" ";
	pars_tabl[1][33]="0";
	pars_tabl[2][33]=" ";
	pars_tabl[3][33]="mulop f t' m9";
	pars_tabl[4][33]=" ";
	pars_tabl[5][33]=" ";
	pars_tabl[6][33]=" ";
	pars_tabl[7][33]=" ";
	pars_tabl[8][33]=" ";
	pars_tabl[9][33]=" ";
	pars_tabl[10][33]=" ";
	pars_tabl[11][33]=" ";
	pars_tabl[12][33]=" ";
	pars_tabl[13][33]=" ";
	pars_tabl[14][33]=" ";
	pars_tabl[15][33]=" ";
	pars_tabl[16][33]=" ";
	pars_tabl[17][33]=" ";
	pars_tabl[18][33]=" ";
	pars_tabl[19][33]=" ";
	pars_tabl[20][33]=" ";
	pars_tabl[21][33]=" ";
	pars_tabl[22][33]=" ";
	pars_tabl[23][33]=" ";
	pars_tabl[24][33]=" ";
	pars_tabl[25][33]=" ";
	pars_tabl[26][33]=" ";
	pars_tabl[27][33]=" ";
	pars_tabl[28][33]=" ";
	pars_tabl[29][33]=" ";
	pars_tabl[30][33]=" ";
	pars_tabl[31][33]=" ";
	pars_tabl[32][33]=" ";
	pars_tabl[33][33]=" ";
	pars_tabl[34][33]=" ";
	pars_tabl[35][33]="mod";
	pars_tabl[36][33]=" ";
	pars_tabl[37][33]=" ";
	pars_tabl[38][33]=" ";
	pars_tabl[39][33]=" ";
	pars_tabl[40][33]=" ";

// =
	pars_tabl[0][34]=" ";
	pars_tabl[1][34]="0";
	pars_tabl[2][34]=" ";
	pars_tabl[3][34]="0";
	pars_tabl[4][34]=" ";
	pars_tabl[5][34]="0";
	pars_tabl[6][34]=" ";
	pars_tabl[7][34]="relop s_e m10";
	pars_tabl[8][34]=" ";
	pars_tabl[9][34]=" ";
	pars_tabl[10][34]=" ";
	pars_tabl[11][34]=" ";
	pars_tabl[12][34]=" ";
	pars_tabl[13][34]=" ";
	pars_tabl[14][34]=" ";
	pars_tabl[15][34]=" ";
	pars_tabl[16][34]=" ";
	pars_tabl[17][34]=" ";
	pars_tabl[18][34]=" ";
	pars_tabl[19][34]=" ";
	pars_tabl[20][34]=" ";
	pars_tabl[21][34]=" ";
	pars_tabl[22][34]=" ";
	pars_tabl[23][34]=" ";
	pars_tabl[24][34]=" ";
	pars_tabl[25][34]=" ";
	pars_tabl[26][34]=" ";
	pars_tabl[27][34]=" ";
	pars_tabl[28][34]=" ";
	pars_tabl[29][34]=" ";
	pars_tabl[30][34]=" ";
	pars_tabl[31][34]=" ";
	pars_tabl[32][34]=" ";
	pars_tabl[33][34]=" ";
	pars_tabl[34][34]=" ";
	pars_tabl[35][34]=" ";
	pars_tabl[36][34]=" ";
	pars_tabl[37][34]=" ";
	pars_tabl[38][34]=" ";
	pars_tabl[39][34]="=";
	pars_tabl[40][34]=" ";
// <>
	pars_tabl[0][35]=" ";
	pars_tabl[1][35]="0";
	pars_tabl[2][35]=" ";
	pars_tabl[3][35]="0";
	pars_tabl[4][35]=" ";
	pars_tabl[5][35]="0";
	pars_tabl[6][35]=" ";
	pars_tabl[7][35]="relop s_e m10";
	pars_tabl[8][35]=" ";
	pars_tabl[9][35]=" ";
	pars_tabl[10][35]=" ";
	pars_tabl[11][35]=" ";
	pars_tabl[12][35]=" ";
	pars_tabl[13][35]=" ";
	pars_tabl[14][35]=" ";
	pars_tabl[15][35]=" ";
	pars_tabl[16][35]=" ";
	pars_tabl[17][35]=" ";
	pars_tabl[18][35]=" ";
	pars_tabl[19][35]=" ";
	pars_tabl[20][35]=" ";
	pars_tabl[21][35]=" ";
	pars_tabl[22][35]=" ";
	pars_tabl[23][35]=" ";
	pars_tabl[24][35]=" ";
	pars_tabl[25][35]=" ";
	pars_tabl[26][35]=" ";
	pars_tabl[27][35]=" ";
	pars_tabl[28][35]=" ";
	pars_tabl[29][35]=" ";
	pars_tabl[30][35]=" ";
	pars_tabl[31][35]=" ";
	pars_tabl[32][35]=" ";
	pars_tabl[33][35]=" ";
	pars_tabl[34][35]=" ";
	pars_tabl[35][35]=" ";
	pars_tabl[36][35]=" ";
	pars_tabl[37][35]=" ";
	pars_tabl[38][35]=" ";
	pars_tabl[39][35]="<>";
	pars_tabl[40][35]=" ";
// <
	pars_tabl[0][36]=" ";
	pars_tabl[1][36]="0";
	pars_tabl[2][36]=" ";
	pars_tabl[3][36]="0";
	pars_tabl[4][36]=" ";
	pars_tabl[5][36]="0";
	pars_tabl[6][36]=" ";
	pars_tabl[7][36]="relop s_e m10";
	pars_tabl[8][36]=" ";
	pars_tabl[9][36]=" ";
	pars_tabl[10][36]=" ";
	pars_tabl[11][36]=" ";
	pars_tabl[12][36]=" ";
	pars_tabl[13][36]=" ";
	pars_tabl[14][36]=" ";
	pars_tabl[15][36]=" ";
	pars_tabl[16][36]=" ";
	pars_tabl[17][36]=" ";
	pars_tabl[18][36]=" ";
	pars_tabl[19][36]=" ";
	pars_tabl[20][36]=" ";
	pars_tabl[21][36]=" ";
	pars_tabl[22][36]=" ";
	pars_tabl[23][36]=" ";
	pars_tabl[24][36]=" ";
	pars_tabl[25][36]=" ";
	pars_tabl[26][36]=" ";
	pars_tabl[27][36]=" ";
	pars_tabl[28][36]=" ";
	pars_tabl[29][36]=" ";
	pars_tabl[30][36]=" ";
	pars_tabl[31][36]=" ";
	pars_tabl[32][36]=" ";
	pars_tabl[33][36]=" ";
	pars_tabl[34][36]=" ";
	pars_tabl[35][36]=" ";
	pars_tabl[36][36]=" ";
	pars_tabl[37][36]=" ";
	pars_tabl[38][36]=" ";
	pars_tabl[39][36]="<";
	pars_tabl[40][36]=" ";

// <=
	pars_tabl[0][37]=" ";
	pars_tabl[1][37]="0";
	pars_tabl[2][37]=" ";
	pars_tabl[3][37]="0";
	pars_tabl[4][37]=" ";
	pars_tabl[5][37]="0";
	pars_tabl[6][37]=" ";
	pars_tabl[7][37]="relop s_e m10";
	pars_tabl[8][37]=" ";
	pars_tabl[9][37]=" ";
	pars_tabl[10][37]=" ";
	pars_tabl[11][37]=" ";
	pars_tabl[12][37]=" ";
	pars_tabl[13][37]=" ";
	pars_tabl[14][37]=" ";
	pars_tabl[15][37]=" ";
	pars_tabl[16][37]=" ";
	pars_tabl[17][37]=" ";
	pars_tabl[18][37]=" ";
	pars_tabl[19][37]=" ";
	pars_tabl[20][37]=" ";
	pars_tabl[21][37]=" ";
	pars_tabl[22][37]=" ";
	pars_tabl[23][37]=" ";
	pars_tabl[24][37]=" ";
	pars_tabl[25][37]=" ";
	pars_tabl[26][37]=" ";
	pars_tabl[27][37]=" ";
	pars_tabl[28][37]=" ";
	pars_tabl[29][37]=" ";
	pars_tabl[30][37]=" ";
	pars_tabl[31][37]=" ";
	pars_tabl[32][37]=" ";
	pars_tabl[33][37]=" ";
	pars_tabl[34][37]=" ";
	pars_tabl[35][37]=" ";
	pars_tabl[36][37]=" ";
	pars_tabl[37][37]=" ";
	pars_tabl[38][37]=" ";
	pars_tabl[39][37]="<=";
	pars_tabl[40][37]=" ";
// >
	pars_tabl[0][38]=" ";
	pars_tabl[1][38]="0";
	pars_tabl[2][38]=" ";
	pars_tabl[3][38]="0";
	pars_tabl[4][38]=" ";
	pars_tabl[5][38]="0";
	pars_tabl[6][38]=" ";
	pars_tabl[7][38]="relop s_e m10";
	pars_tabl[8][38]=" ";
	pars_tabl[9][38]=" ";
	pars_tabl[10][38]=" ";
	pars_tabl[11][38]=" ";
	pars_tabl[12][38]=" ";
	pars_tabl[13][38]=" ";
	pars_tabl[14][38]=" ";
	pars_tabl[15][38]=" ";
	pars_tabl[16][38]=" ";
	pars_tabl[17][38]=" ";
	pars_tabl[18][38]=" ";
	pars_tabl[19][38]=" ";
	pars_tabl[20][38]=" ";
	pars_tabl[21][38]=" ";
	pars_tabl[22][38]=" ";
	pars_tabl[23][38]=" ";
	pars_tabl[24][38]=" ";
	pars_tabl[25][38]=" ";
	pars_tabl[26][38]=" ";
	pars_tabl[27][38]=" ";
	pars_tabl[28][38]=" ";
	pars_tabl[29][38]=" ";
	pars_tabl[30][38]=" ";
	pars_tabl[31][38]=" ";
	pars_tabl[32][38]=" ";
	pars_tabl[33][38]=" ";
	pars_tabl[34][38]=" ";
	pars_tabl[35][38]=" ";
	pars_tabl[36][38]=" ";
	pars_tabl[37][38]=" ";
	pars_tabl[38][38]=" ";
	pars_tabl[39][38]=">";
	pars_tabl[40][38]=" ";
// >=
	pars_tabl[0][39]=" ";
	pars_tabl[1][39]="0";
	pars_tabl[2][39]=" ";
	pars_tabl[3][39]="0";
	pars_tabl[4][39]=" ";
	pars_tabl[5][39]="0";
	pars_tabl[6][39]=" ";
	pars_tabl[7][39]="relop s_e m10";
	pars_tabl[8][39]=" ";
	pars_tabl[9][39]=" ";
	pars_tabl[10][39]=" ";
	pars_tabl[11][39]=" ";
	pars_tabl[12][39]=" ";
	pars_tabl[13][39]=" ";
	pars_tabl[14][39]=" ";
	pars_tabl[15][39]=" ";
	pars_tabl[16][39]=" ";
	pars_tabl[17][39]=" ";
	pars_tabl[18][39]=" ";
	pars_tabl[19][39]=" ";
	pars_tabl[20][39]=" ";
	pars_tabl[21][39]=" ";
	pars_tabl[22][39]=" ";
	pars_tabl[23][39]=" ";
	pars_tabl[24][39]=" ";
	pars_tabl[25][39]=" ";
	pars_tabl[26][39]=" ";
	pars_tabl[27][39]=" ";
	pars_tabl[28][39]=" ";
	pars_tabl[29][39]=" ";
	pars_tabl[30][39]=" ";
	pars_tabl[31][39]=" ";
	pars_tabl[32][39]=" ";
	pars_tabl[33][39]=" ";
	pars_tabl[34][39]=" ";
	pars_tabl[35][39]=" ";
	pars_tabl[36][39]=" ";
	pars_tabl[37][39]=" ";
	pars_tabl[38][39]=" ";
	pars_tabl[39][39]=">=";
	pars_tabl[40][39]=" ";

// <<
	pars_tabl[0][40]=" ";
	pars_tabl[1][40]=" ";
	pars_tabl[2][40]=" ";
	pars_tabl[3][40]=" ";
	pars_tabl[4][40]=" ";
	pars_tabl[5][40]=" ";
	pars_tabl[6][40]=" ";
	pars_tabl[7][40]=" ";
	pars_tabl[8][40]=" ";
	pars_tabl[9][40]=" ";
	pars_tabl[10][40]=" ";
	pars_tabl[11][40]=" ";
	pars_tabl[12][40]=" ";
	pars_tabl[13][40]=" ";
	pars_tabl[14][40]="<< e_l m11";
	pars_tabl[15][40]=" ";
	pars_tabl[16][40]="st st_l'";
	pars_tabl[17][40]=" ";
	pars_tabl[18][40]="st_l";
	pars_tabl[19][40]=" ";
	pars_tabl[20][40]=" ";
	pars_tabl[21][40]=" ";
	pars_tabl[22][40]=" ";
	pars_tabl[23][40]=" ";
	pars_tabl[24][40]=" ";
	pars_tabl[25][40]=" ";
	pars_tabl[26][40]=" ";
	pars_tabl[27][40]=" ";
	pars_tabl[28][40]=" ";
	pars_tabl[29][40]=" ";
	pars_tabl[30][40]=" ";
	pars_tabl[31][40]=" ";
	pars_tabl[32][40]=" ";
	pars_tabl[33][40]=" ";
	pars_tabl[34][40]=" ";
	pars_tabl[35][40]=" ";
	pars_tabl[36][40]=" ";
	pars_tabl[37][40]=" ";
	pars_tabl[38][40]=" ";
	pars_tabl[39][40]=" ";
	pars_tabl[40][40]=" ";

// >>
	pars_tabl[0][41]=" ";
	pars_tabl[1][41]=" ";
	pars_tabl[2][41]=" ";
	pars_tabl[3][41]=" ";
	pars_tabl[4][41]=" ";
	pars_tabl[5][41]=" ";
	pars_tabl[6][41]=" ";
	pars_tabl[7][41]=" ";
	pars_tabl[8][41]=" ";
	pars_tabl[9][41]=" ";
	pars_tabl[10][41]=" ";
	pars_tabl[11][41]=" ";
	pars_tabl[12][41]=" ";
	pars_tabl[13][41]=" ";
	pars_tabl[14][41]=" >> m12 id_l m32 ";
	pars_tabl[15][41]=" ";
	pars_tabl[16][41]="st st_l'";
	pars_tabl[17][41]=" ";
	pars_tabl[18][41]="st_l";
	pars_tabl[19][41]=" ";
	pars_tabl[20][41]=" ";
	pars_tabl[21][41]=" ";
	pars_tabl[22][41]=" ";
	pars_tabl[23][41]=" ";
	pars_tabl[24][41]=" ";
	pars_tabl[25][41]=" ";
	pars_tabl[26][41]=" ";
	pars_tabl[27][41]=" ";
	pars_tabl[28][41]=" ";
	pars_tabl[29][41]=" ";
	pars_tabl[30][41]=" ";
	pars_tabl[31][41]=" ";
	pars_tabl[32][41]=" ";
	pars_tabl[33][41]=" ";
	pars_tabl[34][41]=" ";
	pars_tabl[35][41]=" ";
	pars_tabl[36][41]=" ";
	pars_tabl[37][41]=" ";
	pars_tabl[38][41]=" ";
	pars_tabl[39][41]=" ";
	pars_tabl[40][41]=" ";

	pars_tabl[0][42]=" ";
	pars_tabl[1][42]=" ";
	pars_tabl[2][42]=" ";
	pars_tabl[3][42]=" ";
	pars_tabl[4][42]=" ";
	pars_tabl[5][42]=" ";
	pars_tabl[6][42]=" ";
	pars_tabl[7][42]=" ";
	pars_tabl[8][42]=" ";
	pars_tabl[9][42]=" ";
	pars_tabl[10][42]=" ";
	pars_tabl[11][42]=" ";
	pars_tabl[12][42]=" ";
	pars_tabl[13][42]=" ";
	pars_tabl[14][42]=" ";
	pars_tabl[15][42]=" ";
	pars_tabl[16][42]=" ";
	pars_tabl[17][42]=" ";
	pars_tabl[18][42]=" ";
	pars_tabl[19][42]=" ";
	pars_tabl[20][42]=" ";
	pars_tabl[21][42]=" ";
	pars_tabl[22][42]=" ";
	pars_tabl[23][42]=" ";
	pars_tabl[24][42]=" ";
	pars_tabl[25][42]=" ";
	pars_tabl[26][42]=" ";
	pars_tabl[27][42]=" ";
	pars_tabl[28][42]=" ";
	pars_tabl[29][42]=" ";
	pars_tabl[30][42]=" ";
	pars_tabl[31][42]=" ";
	pars_tabl[32][42]=" ";
	pars_tabl[33][42]=" ";
	pars_tabl[34][42]=" ";
	pars_tabl[35][42]=" ";
	pars_tabl[36][42]=" ";
	pars_tabl[37][42]=" ";
	pars_tabl[38][42]=" ";
	pars_tabl[39][42]=" ";
	pars_tabl[40][42]=" ";




}

int Parser::get_up(int a)// this function returns the index of the token in the terminals array
{
	switch(a)
	{
		case 1:
			return 5;

		case 2:
			return 28;

		case 3:
			return 27;
		
		case 4:
			return 34;

		case 5:
			return 35;

		case 6:
			return 36;

		case 7:
			return 37;

		case 8:
			return 39;

		case 9:
			return 38;

		case 10:
			return 0;

		case 11:
			return 1;

		case 12:
			return 30;

		case 13:
			return 31;

		case 14:
			return 15;

		case 15:
			return 32;

		case 16:
			return 20;

		case 17:
			return 11;

		case 18:
			return 13;

		case 19:
			return 16;

		case 20:
			return 12;

		case 21:
			return 18;

		case 22:
			return 33;

		case 23:
			return 21;

		case 24:
			return 29;

		case 25:
			return 17;

		case 26:
			return 23;

		case 27:
			return 19;

		case 28:
			return 14;

		case 29:
			return 22;

		case 30:
			return 10;

		case 31:
			return 26;

		case 32:
			return 3;

		case 33:
			return 4;

		case 34:
			return 6;

		case 35:
			return 9;

		case 36:
			return 7;

		case 37:
			return 8;

		case 38:
			return 24;

		case 39:
			return 25;

		case 40:
			return 45;// chk 4 the error in lex lexeme
		
		case 41:
			return 40;

		case 42:
			return 41;

		case 43:
			return 2;

		case 44:
			return 42;

	}//end switch
}


int Parser::is_terminal(string ter)// this returns the index if terminal else 43
{
	for(int i=0;i<size_up;i++)
	{
			if(ter==up[i])
			return i;
	}	
	//string s1("m1"),s2("m2"),s3("m3"),s4("m4");

	//if(ter==s1 || ter==s2 || ter==s3 || ter==s4) return i;//if any marker return 43
		

	
	
	return i;
}

int Parser::is_non_terminal(string ter)// returns the index in the non_terminal array if not there thn it returns 41
{
	for(int i=0;i<41;i++)
	{
		if(ter==left[i])
			return i;
	}
	return i;
}

void Parser::set_left_up()// sets the left nd up of the production to b fired 
{							//it gets the terminal from 'token' and non-terminal from tos
	iup=get_up(token);
	for(int i=0;i<41;i++)
	{
		if(pars_stack.top() == left[i])
		{
			ileft=i;
			break;
		}
	}
}

int Parser::fire_production() // fires the production
{
	int size=pars_tabl[ileft][iup].length();// gets size of the production string
	

	if(pars_tabl[ileft][iup]==" ")// if no entry thr error print & return
	{
		//cout<<"ileft= "<<ileft<<" iup= "<<iup<<" \n";// written 2 chk the location of error
		cout<<"\nunexpected symbol "<<up[iup]<<"\nSyntax Error:no production here : "<<left[ileft]<<" --> "<<up[iup]<<"\n";
		return 0;
	}
	
	if(pars_tabl[ileft][iup]=="0")//just pop the stack in case of NULL
	{
		pars_stack.pop();// pop the previous symbol on the stack
		return 1;// production fired successfully
	}

	char * production=new char[size+1];// this used 2 convert the string to pish on the stack
	pars_tabl[ileft][iup].copy(production,size,0);// save the production in the char * array
	production[size]= 0;

	char * push_production=new char[size+1];// used to invert input that is to b pushed on stack


	for(int i=1;i<=size;i++)// invert the production
		push_production[size-i]=production[i-1];
	push_production[size]=0;
	pars_stack.pop();// pop the previous symbol on the stack

	char * tokenptr;// used to get the tokens to b pushed on the stack
	tokenptr = strtok(push_production," ");// get 1st token

	while(tokenptr != NULL)// run till last token
	{
		int i=strlen(tokenptr);//
		char * push_token=new char[i+1];// as token got is inverted so this is used to change it to droginal form	
		
		for(int j=1;j<=i;j++)// invert the input suppose s_c -> c_s
			push_token[j-1]=tokenptr[i-j];
		push_token[j-1]=0;
	
		string temp(push_token);// change char* to string final string to b pushed	
		int check=0;//cheks whether production is terminal or non
		
		// 1st get the location of the token 2 b pushed in terminal or non-termianl array , as stack saves this reference not the priginal string
		check=is_terminal(temp); // chk whther the string to b pushed is terminal
		if(check < size_up )// if <43 it is index in up array, else if >43 it is a marker, otherwise  not present there
			pars_stack.push(up[check]);// push on stack,stack gets the index in array
		else
		{
			check=is_non_terminal(temp);//check the production in non terminals
			pars_stack.push(left[check]);//push in the stack
		}
		//cout<<pars_stack.top()<<"\n";// used to see the last production pushed
		tokenptr = strtok( NULL , " ");//call for next token
		delete [] push_token;

	}
	delete [] production;
	delete [] push_production;

	return 1;//fired successfully
}


void Parser::call_mrkr(stack <Avltree*> & stk)
{
	call_marker=false;//set the flag to false
	
	if(marker=="m3")
	{
		evaluate_stack.push(pars_stack.top());//push type to b assigned on the top of the stack
		mark.marker3(evaluate_stack,stk);
		return;
	}

	if(marker=="m5")
	{
		evaluate_stack.push(pars_stack.top());//push type to b assigned on the top of the stack
		mark.marker5(evaluate_stack,stk);
		return;
	}

}

int Parser::check(stack <Avltree*> & stk,Lex &lex1)//if the token given by lex is terminal pop it and return 1, else return 2 
{
	
	string str=pars_stack.top();//used temporary to see the string at tis
	int vari=get_up(token);// get the index of the token in the up array
	int ii=is_terminal(pars_stack.top());//check the tos is terminal or not
	
	
	
	if(ii < size_up)//if terminal pop it 
	{
		if(ii<43)//if any nonterminal,simply pop it & also put it on the evaluate stack;
		{
			if(pars_stack.top() == up[vari])// if tos and input from the lex is same pop it
			{
				//if(vari==5)// if index in array left  = id tyhen push the var on 2nd stack
				//	evaluate_stack.push(pars_stack.top());//put the variable on the evuluator stack
				if(!call_marker)
				{
					pars_stack.pop();
					input_flag=true;
					return 1;// if pop successful
				
				}

				else
				{
					call_mrkr(stk);

					pars_stack.pop();
					input_flag=true;
					return 1;// if pop successful

				}
			}
			else // if TOS is terminal and does naot match the input it is eror reurn
			{
				cout<<"\nsyntax error,";
				return 0;//pop unsuccessful
			}
		}

		else 
		{
			bool t;
			switch(ii)
			{
				case 43:// m3
		
					call_marker=true;//call marker in the pop nxt time
					marker="m3";//call thios mrkr
					pars_stack.pop();//pop the mrkr
					input_flag=false;
					return 2;//fire the nxt production
				case 44: // m4

					pars_stack.pop();//pop the marker
					input_flag=false;// next input from lex is now alloweds
					evaluate_stack.push("&");
					//cout<<"  "<<evaluate_stack.top();
					
					// call marjer 4 here not needed yet
					return 1;

				case 45: // m1
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker1(evaluate_stack,stk))
					{
						evaluate_stack.push("@");//for chkng of no argmnt function
						return 1;
					}
					else return 3;

				case 46: // m2
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker2(evaluate_stack,stk))
						return 1;
					else return 3;//error of mismatch

				case 47://m5
					call_marker=true;//call marker in the pop nxt time
					marker="m5";//call thios mrkr
					pars_stack.pop();//pop the mrkr
					input_flag=false;
					return 2;//fire the nxt production
					
				case 48://m6 //temporary
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker6(evaluate_stack,stk))
						return 1;
					else return 3;

					return 2;

				case 49://m7
					pars_stack.pop();//pop the marker
					lex1.add_st=false;
					return 2;

				case 50://m8
					pars_stack.pop();//pop the marker
					lex1.add_st=true;
					return 2;
				
				case 51: // m9
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker9(evaluate_stack,stk))
						return 1;
					else return 3;

				case 52: // m10
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker10(evaluate_stack,stk))
						return 1;
					else return 3;
				
				case 53: // m11
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker11(evaluate_stack,stk))
						return 1;
					else return 3;
				
				case 54: // m12
					pars_stack.pop();//pop the marker
					input_flag=false;
					read_flag=true;
					//if(mark.marker12(evaluate_stack,stk))
						return 1;
					//else return 3;

				case 55: // m13
					pars_stack.pop();//pop the marker
					//input_flag=false;
					if(mark.marker13(evaluate_stack,stk))
						return 1;
					else return 3;
				
				case 56: // m14
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker14(evaluate_stack,stk))
						return 1;
					else return 3;
				
				case 57: // m15
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker15(evaluate_stack,stk))
						return 1;
					else return 3;

				case 58: // m16
					pars_stack.pop();//pop the marker
					//input_flag=false;
					if(mark.marker16(evaluate_stack,stk))
						return 1;
					else return 3;

				case 59: // m17
					pars_stack.pop();//pop the marker
					input_flag=false;
					//if(mark.marker17(evaluate_stack,stk))
					if(1)
					{
						AVLnode *a=stk.top()->search(stk.top()->getroot(),evaluate_stack.top());
						a->func_strt=mark.get_line();

						Avltree* t=new Avltree();
						t->set_name(evaluate_stack.top());//set name of the new tree created
						stk.push(t);
					}
					return 1;
				//	else return 3;

				case 60: // m18
					pars_stack.pop();//pop the marker
					input_flag=false;
					mark.marker18(evaluate_stack,stk);
					//cout<<stk.top()->getroot()->get_name()<<"\n";
					//stk.top()->print(stk.top()->getroot());
				//	ii=0;
					//cout<<"\n";
					//cout<<evaluate_stack.top();
					func_stack.push(stk.top());//put the tree to be popped on func stk
					stk.pop();
					if(!act.create(evaluate_stack,stk,func_stack,mark.get_line()+6))
						return 3;
					lex1.add_st=true;
					return 1;
					//else return 3;

				case 61: // m19
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker19(evaluate_stack,stk))
						return 1;
					else return 3;

				case 62: // m20
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker20(evaluate_stack,stk))
					return 1;
					else return 3;


				case 63: // m21 for int 
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker21(evaluate_stack,stk))
					return 1;
					else return 3;
				

				case 64: // m22
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker22(evaluate_stack,stk))
					return 1;
					else return 3;

				case 65: // m23
					pars_stack.pop();//pop the marker
					input_flag=false;
				
					if(1)
					{
						int a=mark.func(evaluate_stack,stk,func_stack,mark.get_line()+6);
						if(a==-1)
							return 3;
						//if(act.create(evaluate_stack,stk,func_stack,mark.get_line()+6+a))
							return 1;
					}
					else return 3;



				case 66: // m24
					pars_stack.pop();//pop the marker
					input_flag=false;
					mark.marker24(evaluate_stack,stk);
					return 1;
					
				case 67: // m25
					pars_stack.pop();//pop the marker
					input_flag=false;
					mark.marker25(evaluate_stack,stk);
					return 1;

				case 68: // m26
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker26(evaluate_stack,stk))
						return 1;
					return 3;

				case 69: // m27
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker27(evaluate_stack,stk))
						return 1;
					return 3;

/*				case 70: // m28
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(mark.marker28(evaluate_stack,stk))
						return 1;
					return 3;

*/				case 71: // m29
					pars_stack.pop();//pop the marker
					cout<<"\nfunction call not allowed here ";
					return 3;
					
				case 72: // m30
					pars_stack.pop();//pop the marker
					if(1)
					{
						string st=evaluate_stack.top();
						input_flag=false;
						string st1("@");
						if(st==st1)//activation record has been called and evrythng ok
						{
							evaluate_stack.pop();
							return 1;
						}

						else
						{	
							bool tt=mark.check_global_fun(stk,evaluate_stack.top());
							if(tt)
							{
								pars_stack.push("m23");
								evaluate_stack.push("&");
							}
							return 1;
						}
					}

				case 73: // m31
					pars_stack.pop();//pop the marker
					input_flag=false;
					if(read_flag)
					{
						if(mark.marker12(evaluate_stack,stk))
						{
							//read_flag=false;
							return 1;
						
						}
						else return 3;
					}
					return 1;
					

				case 74: // m32
					pars_stack.pop();//pop the marker
					input_flag=false;
					read_flag=false;
					return 1;

					
				default:
					break;
			}//switch
		}//else 
	}//main if	

	return 2;//tos is non terminal fire a production
}

void Parser::parse(Lex &lex1,stack<Avltree*> &stk)
{
	int i=0;
	while(1)//  run till end of iunput
	{
		if(input_flag)// if previous symbol consumed thn take next input
		{
			token=lex1.analyse(stk,this->evaluate_stack);// call LEX to get next token
			cout<<this->evaluate_stack.top()<<" ";
		
		}
		
		if(token == 40)// token=40 is for lex error
		{
			cout<<"\nLexical error,invalid lexeme at line no."<<lex1.get_line_num()<<"\n";
			return;
		}

		
		if(token == 50)// token-50 is for end of input
		{
			//cout<<"\nTOS : "<<pars_stack.top();//show the symbol on TOS

			string s("m28");
			if(pars_stack.top() == s)// see if TOS is '$' at end
			{
				pars_stack.pop();
				mark.marker28(evaluate_stack,stk);
				cout<<"\nTOS : "<<pars_stack.top();//show the symbol on TOS

				cout<<"\nparsing terminated successful\n";// if yes 
				return;
			}
			else
				cout<<"\nthe input has fifnished & parsing terminated incomplete\n";
			return;
		}

		if(token == 51)// token=40 is for lex error
		{
			cout<<"at line "<<lex1.get_line_num()<<"\n";
			return;
		}

		
		i=check(stk,lex1);// this will pop if tos is terminal and return 2 if terminal
				  // return 0 if input symbol and tos does naot match
		
		if(i==0)// if an error has occure then move back
		{
			cout<<"\nunexpexted input symbol "<<up[get_up(token)]<<" symbol expected is"<<pars_stack.top()<<" at line no."<<lex1.get_line_num()<<"\n"; 
			return;//return to main
		}

		if(i==3)
		{
			cout<<" at line no."<<lex1.get_line_num()<<"\n"; 
			return;//return to main
		}
		if(i==2)// if non-terminal then fire production
		{

			
			input_flag=false;// do not take input till this input consuned
			set_left_up();// set the index of the pars tabl
			i=fire_production();// fire the production

			if(i==0) // if any error during fire of production
			{
				cout<<"at line no."<<lex1.get_line_num()<<"\n";
				return;//production not fired return to main

			}

		}//end if
	}//end while
	
}


void Parser::initialiaze(Lex lex1)
{
	string s("$");
	pars_stack.push(s);//push $ at the bottom of the stack
	
	evaluate_stack.push(s);//push $ at the bottom of the stack

	s="start";
	pars_stack.push(s);//push start production  bottom of the stack
	//ofstream mcout("code.txt",ios::out);
	
}
