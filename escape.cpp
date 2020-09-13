#include <bangtal.h>
using namespace bangtal;



// 'escape'를 의미하는 여섯 개의 조각을 찾아 조립판에 끼워 넣어야 탈출할 수 있다. 이전 모험가의 메모가 힌트.

int main()
{
	// 1. 장면을 생성한다.
	auto scene1 = Scene::create("룸1", "images/배경-1.png");
	auto scene2 = Scene::create("룸2", "images/배경-2.png");

	// 3. 문을 만든다.
	auto open1 = false;
	auto door1 = Object::create("images/문-오른쪽-열림.png", scene1, 740, 283);
	auto door2 = Object::create("images/문-왼쪽-열림.png", scene2, 320, 270);
	auto hidden_door = Object::create("images/문-왼쪽-열림.png", scene1, 220, 283, false);

	hidden_door->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		endGame();
		return true;
		});


	door2->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene1->enter();
		return true;
		});

	door1->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		scene2->enter();

		return true;
		});

	auto hand_A = false;
	auto hand_C = false;
	auto hand_S = false;
	auto hand_E = false;

	// 3-3. A조각을 만든다.
	auto piece_A = Object::create("Images/A조각.png", scene1, 1030, 430);
	piece_A->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		piece_A->pick();
		hand_A = true;

		if (hand_A == true && hand_C == true && hand_S == true && hand_E == true) {
			showMessage("모든 조각을 다 모았다! 게시판을 확인하자!");
		}

		return true;
		});

	// 2. 코르크 게시판을 만든다.
	auto board = Object::create("Images/코르크판-벽.png", scene1, 930, 380);
	auto big_board = Object::create("Images/코르크판-확대.png", scene1, 360, 130, false);
	auto complete_board = Object::create("Images/코르크판-완성.png", scene1, 360, 130, false);
	big_board->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		big_board->hide();
		return true;
	});
	complete_board->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		complete_board->hide();
		return true;
		});

	// 3-1. C조각을 만든다.
	auto piece_C = Object::create("Images/C조각.png", scene1, 990, 180);
	piece_C->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		piece_C->pick();

		if (hand_A == true && hand_C == true && hand_S == true && hand_E == true) {
			showMessage("모든 조각을 다 모았다! 게시판을 확인하자!");
		}

		hand_C = true;

		return true;
	});

	// 3-2. S조각을 만든다.
	auto piece_S = Object::create("Images/S조각.png", scene2, 720, 530);
	piece_S->setScale(0.7f);
	piece_S->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		piece_S->pick();
		hand_S = true;

		if (hand_A == true && hand_C == true && hand_S == true && hand_E == true) {
			showMessage("모든 조각을 다 모았다! 게시판을 확인하자!");
		}

		return true;
	});
	
	// 3-2'. 달력을 만든다.
	auto calendar = Object::create("Images/달력.png", scene2, 700, 525);
	auto calendar_moved = false;
	calendar->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		if (calendar_moved == false) {
			if (action == MouseAction::MOUSE_DRAG_DOWN) {
				calendar->locate(scene2, 700, 300);
				calendar_moved = true;
			}
		}
		return true;
		});

	// 3-4'. 책상을 만든다.
	auto desk = Object::create("Images/책상세트.png", scene2, 900, 210);

	// 3-4. E조각을 만든다.
	auto piece_E = Object::create("Images/E조각.png", scene2, 1060, 360);
	piece_E->setScale(0.1f);
	piece_E->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		piece_E->pick();
		hand_E = true;

		if (hand_A == true && hand_C == true && hand_S == true && hand_E == true) {
			showMessage("모든 조각을 다 모았다! 게시판을 확인하자!");
		}

		return true;
		});


		board->setOnMouseCallback([&](ObjectPtr object, int x, int y, MouseAction action)->bool {
		// 2'. 코르크 게시판이 클릭하면 확대되고 드래그하면 움직이게 한다.
		if (action == MouseAction::MOUSE_DRAG_DOWN) {
			board->locate(scene1, 930, 220);
		}

		if (action != MouseAction::MOUSE_DRAG_DOWN) {
			if (hand_A == true && hand_C == true && hand_S == true && hand_E == true) {
				complete_board->show();
				hidden_door->show();
			}
			else
				big_board->show();
			
		}

		return true;
	});

	
	// 0. 게임을 시작한다.
	startGame(scene1);

	return 0;
}