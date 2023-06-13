#pragma once

class ACTION {
public:
	ACTION();
	void Out() {
		Cal();
		Cha();
	}
private:
	struct
	{
		int Typ[8][8];
		int X[8][8];
		int Y[8][8];
	}Sto;

	struct
	{
		int X = 0;
		int Y = 0;
	}Cur;

	struct
	{
		bool Xr = 0;
		bool Xl = 0;
		bool Yu = 0;
		bool Yd = 0;
		bool Ent = 0;
	}Fla;

	int Tur = 0;

	struct
	{
		struct
		{
			int r;
			int m;
			int l;
		}x;
		struct
		{
			int u;
			int m;
			int d;
		}y;

	}e;

	void Cal();
	void Cha();
};

ACTION Act;

ACTION::ACTION() {
	for (int y = 0; y < 8; y = y + 1) {
		for (int x = 0; x < 8; x = x + 1) {
			Sto.Typ[x][y] = 0;
			Sto.X[x][y] = 0;
			Sto.Y[x][y] = 0;
		}
	}
	//黒
	Sto.Typ[3][3] = 1;
	Sto.X[3][3] = 3 * 100;
	Sto.Y[3][3] = 3 * 100;

	Sto.Typ[4][4] = 1;
	Sto.X[4][4] = 4 * 100;
	Sto.Y[4][4] = 4 * 100;

	//白
	Sto.Typ[3][4] = 2;
	Sto.X[3][4] = 3 * 100;
	Sto.Y[3][4] = 4 * 100;

	Sto.Typ[4][3] = 2;
	Sto.X[4][3] = 4 * 100;
	Sto.Y[4][3] = 3 * 100;


}

void ACTION::Cal() {
	//移動処理
	if (Key.Inf[KEY_INPUT_D] == 1)Fla.Xr = 1;
	else if (Key.Inf[KEY_INPUT_A] == 1)Fla.Xl = 1;
	else if (Key.Inf[KEY_INPUT_W] == 1)Fla.Yd = 1;
	else if (Key.Inf[KEY_INPUT_S] == 1)Fla.Yu = 1;

	if (Fla.Xr == 1)Cur.X = Cur.X + 100;
	else if (Fla.Xl == 1)Cur.X = Cur.X - 100;
	else if (Fla.Yd == 1)Cur.Y = Cur.Y - 100;
	else if (Fla.Yu == 1)Cur.Y = Cur.Y + 100;

	//移動範囲制限
	if (Cur.X < 0)Cur.X = 0;
	if (Cur.X > 800 - 100) {
		Cur.X = 800 - 100;
	}
	if (Cur.Y < 0)Cur.Y = 0;
	if (Cur.Y > 800 - 100) {
		Cur.Y = 800 - 100;
	}

	//Enterキー決定
	if (Key.Inf[KEY_INPUT_NUMPADENTER] == 1) {
		Fla.Ent = 1;
	}
	//石を交互に置く
	for (int y = 0; y < 8; y = y + 1) {
		for (int x = 0; x < 8; x = x + 1) {
			if (Cur.X == 100 * x &&
				Cur.Y == 100 * y &&
				Fla.Ent == 1 &&
				Sto.Typ[x][y] == 0) {
				Tur = Tur + 1;
				Sto.X[x][y] = Cur.X;
				Sto.Y[x][y] = Cur.Y;
				//偶数の場合は白
				if (Tur % 2 == 0) {
					Sto.Typ[x][y] = 2;
				}
				//奇数の場合は黒
				else {
					Sto.Typ[x][y] = 1;
				}

			}
		}
	}

	e.y.m = Cur.X / 100;
	e.y.m = Cur.Y / 100;

	e.x.r = e.x.m + 1;
	e.x.l = e.x.m - 1;
	e.y.u = e.y.m - 1;
	e.y.d = e.y.m + 1;

	if (Fla.Ent == 1) {
		int same;
		int diff;
		//白のターン
		if (Tur % 2 == 0) {
			same = 2;
			diff = 1;
		}
		//黒のターン
		else {
			same = 1;
			diff = 2;
		}

		int cou = 0;
		//right
		for (int x = e.x.r; x < 8; x = x + 1) {
			if (Sto.Typ[x][e.y.m] == 0)break;
			else if (Sto.Typ[x][e.y.m] == same) {
				for (int x = e.x.r; x < e.x.r + cou; x = x + 1) {
					Sto.Typ[x][e.y.m] = same;
				}break;
			}
			else if (Sto.Typ[x][e.y.m] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;
		//left
		for (int x = e.x.l; x > 0; x = x - 1) {
			int b = 0;
			if (Sto.Typ[x][e.y.m] == 0)break;
			else if (Sto.Typ[x][e.y.m] == same) {
				for (int x = e.x.l; x > e.x.l - cou; x = x - 1) {
					Sto.Typ[x][e.y.m] = same;
				}break;
			}
			else if (Sto.Typ[x][e.y.m] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;
		//down
		for (int y = e.y.d; y < 8; y = y + 1) {
			if (Sto.Typ[e.x.m][y] == 0)break;
			else if (Sto.Typ[e.x.m][y] == same) {
				for (int y = e.y.d; y < e.y.d + cou; y = y + 1) {
					Sto.Typ[e.x.m][y] = same;
				}break;
			}
			else if (Sto.Typ[e.x.m][y] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;

		//up
		for (int y = e.y.u; y > 0; y = y - 1) {
			if (Sto.Typ[e.x.m][y] == 0)break;
			else if (Sto.Typ[e.x.m][y] == same) {
				for (int y = e.y.u; y > e.y.u - cou; y = y - 1) {
					Sto.Typ[e.x.m][y] = same;
				}break;
			}
			else if (Sto.Typ[e.x.m][y] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;

		//right_down
		int x, y;
		for (x = e.x.r, y = e.y.d; x < 8, y < 8; x = x + 1, y = y + 1) {
			if (Sto.Typ[x][y] == 0)break;
			else if (Sto.Typ[x][y] == same) {
				for (x = e.x.r, y = e.y.d; x < e.x.r + cou, y < e.y.d + cou; x = x + 1, y = y + 1) {
					Sto.Typ[x][y] = same;
				}break;
			}
			else if (Sto.Typ[x][y] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;

		//right_up
		for (x = e.x.r, y = e.y.u; x < 8, y > 0; x = x + 1, y = y - 1) {
			if (Sto.Typ[x][y] == 0)break;
			else if (Sto.Typ[x][y] == same) {
				for (x = e.x.r, y = e.y.u; x < e.x.r + cou, y > e.y.u - cou; x = x + 1, y = y - 1) {
					Sto.Typ[x][y] = same;
				}break;
			}
			else if (Sto.Typ[x][y] == diff)cou = cou + 1;
			else break;
		}
		cou = 0;

		//left_down
		for ( x = e.x.l, y = e.y.d; x > 0, y < 8; x = x - 1, y = y + 1 ) {
			if ( Sto.Typ[ x ][ y ] == 0 )break;
			else if ( Sto.Typ[ x ][ y ] == same ) {
				for ( x = e.x.l -cou, y = e.y.d; x > e.x.r - cou, y < e.y.d + cou; x = x - 1, y = y + 1 ) {
					Sto.Typ[ x ][ y ] = same;
				}break;
			} else if ( Sto.Typ[ x ][ y ] == diff )cou = cou + 1;
			else break;
		}
		cou = 0;

		//left_up
		for ( x = e.x.l, y = e.y.u; x > 0, y > 0; x = x - 1, y = y - 1 ) {
			if ( Sto.Typ[ x ][ y ] == 0 )break;
			else if ( Sto.Typ[ x ][ y ] == same ) {
				for ( x = e.x.l, y = e.y.u; x > e.x.r - cou, y > e.y.u - cou; x = x - 1, y = y - 1 ) {
					Sto.Typ[ x ][ y ] = same;
				}break;
			} else if ( Sto.Typ[ x ][ y ] == diff )cou = cou + 1;
			else break;
		}
		cou = 0;
	}
}

//8*8の板を生成
void ACTION::Cha() {
	for (int y = 0; y < 8; y = y + 1) {
		for (int x = 0; x < 8; x = x + 1) {
			DrawGraph(x * 100, y * 100, Pic.Bac, TRUE);
		}
	}

	int cou_n = 0;
	int cou_b = 0;
	int cou_w = 0;

	for (int y = 0; y < 8; y = y + 1) {
		for (int x = 0; x < 8; x = x + 1) {
			switch (Sto.Typ[x][y])
			{
			case 0:
				cou_n = cou_n + 1;
				break;
			case 1:
				cou_b = cou_b + 1;
				DrawGraph(Sto.X[x][y], Sto.Y[x][y], Pic.Bla, TRUE);
				break;
			case 2:
				cou_w = cou_w + 1;
				DrawGraph(Sto.X[x][y], Sto.Y[x][y], Pic.Whi, TRUE);
				break;
			}
		}
	}

	DrawBox(Cur.X, Cur.Y, Cur.X + 100, Cur.Y + 100, Col.Red, FALSE);
	DrawFormatStringToHandle(900, 0, Col.Bla, Fon.c[30], "(Cur.X,Cur.Y)=(%d,%d)", Cur.X, Cur.Y);

	DrawFormatStringToHandle(900, 50, Col.Bla, Fon.c[30], "(X,Y)=(%d,%d)", (Cur.X + 100) / 100, (Cur.Y + 100) / 100);

	if (Tur % 2 == 0) {
		DrawFormatStringToHandle(900, 100, Col.Blu, Fon.c[30], "%dTurn(Black Attack)", Tur);
	}
	else {
		DrawFormatStringToHandle(900, 100, Col.Red, Fon.c[30], "Turn=%d(White Attack)", Tur);
	}

	DrawFormatStringToHandle(900, 150, Col.Bla, Fon.c[30], "%dTurn(White Attack)", Tur);

	Fla.Xr = 0;
	Fla.Xl = 0;
	Fla.Yd = 0;
	Fla.Yu = 0;
	Fla.Ent = 0;
}


