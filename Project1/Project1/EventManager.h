#pragma once
#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H

#include <iostream>
#include <cstdlib>




using namespace std;

class EventManager {
public:
    static void triggerStageEvent(int battleCount) {
        if (battleCount == 1 || battleCount == 10 || battleCount == 18 || battleCount == 19) {
            // 1, 10, 18, 19번째 스테이지에서만 이벤트 발생
            switch (battleCount) {
            
            case 1:
                cout << "===================================================================================" << endl;
                cout << "갑자기 나타난 몬스터에 당황하는것도 잠시, " << endl;
                cout << "필사적으로 살려고 맞서싸우기 시작했다." << endl;
                cout << "정신없는 전투가 끝나고, 몬스터가 쓰러지더니 이내 가루가 되어 사라졌다." << endl;
                cout << "그순간, 갑자기 뒤에서 웃음소리가 들려왔다." << endl;
                cout << "“낄낄....용케도 그 녀석을 당황하지 않고 금방 때려잡았구만....금방 쓰러질 줄 알았는데 말이지...낄낄...”" << endl;
                cout << "당황한 나는 곧바로 경계하고 전투태세를 갖추었다." << endl;
                cout << "“진정하라고....낄낄....난 싸우려고 이곳에 있는게 아니야....”" << endl;
                cout << "“너와 비슷한 녀석들을 수도없이 만나왔어...낄낄....”" << endl;
                cout << "“방금 저 녀석을 죽이고 재화를 얻었지 ? 그 재화로 너에게 도움이 될만한 물건을 파는 사람이라고...낄낄...”" << endl;
                cout << "“자 그럼 골라봐...낄낄...”" << endl;
                cout << " system: 상점이 추가되었습니다." << endl;
                cout << "===================================================================================" << endl;

                break;
            
            case 10:
                cout << "===================================================================================" << endl;
                cout << "비슷하게 생긴 방들을 10개쯤 지나왔을까, 일정한 패턴들이 반복되고 있다는 것을 느꼈다." << endl;
                cout << "방을 넘어가면 몬스터가 있고, 그녀석을 잡으면 저 불쾌한 상인이 나온다." << endl;
                cout << "앞으로 얼마나 남은지도, 몬스터들도 강해지고 있는거같지만" << endl;
                cout << "나도 점점 강해지고 있다는 느낌이든다." << endl;
                cout << "여기서 쓰러질 순 없다.계속 앞으로 나아가자." << endl;
                cout << "===================================================================================" << endl;
                break;
            
            case 18:
                cout << "===================================================================================" << endl;
                cout << "힘겹게 몬스터와의 전투를 끝냈다." << endl;
                cout << "그러자 갑자기 다음 방에서 알수없는 굉음과 함께, 엄청난 포효소리가 온몸으로 느껴졌다." << endl;
                cout << "이 너머에 지금까지와는 다른 강력한 존재가 있는것이 틀림없다...." << endl;
                cout << "다음 전투는 분명 힘든 전투가 기다리고 있을것이다." << endl;
                cout << "대비를 단단히 해서 가는것이 좋겠다...." << endl;
                cout << "===================================================================================" << endl;
                break;

            case 19:
                cout << "===================================================================================" << endl;
                cout << "10번째 방의 강해보이는 녀석을 처치하고 희미한 빛이 새어 나오는 문으로 향했다." << endl;
                cout << "이 너머에 탈출구가 있을수도 있다는 희망이 내 마음을 요동치게 했다." << endl;
                cout << "하지만 그 끝에 보이는것은 처음 일어났던 방의 모습이었다." << endl;
                cout << "그 문너머로 걸어가는 나의 뒷모습이 어렴풋이 보였다." << endl;
                cout << "이대로 영원히 반복되는 공간 속에 갇혀버린거 같은 상황에 절망이 나를 잠식해 가고있었다." << endl;
                cout << "그순간" << endl;
                cout << "“.....쪽 이....!”" << endl;
                cout << "어디선가 들리는 희미한 소리다." << endl;
                cout << "“....간이 없....!”" << endl;
                cout << "점점 선명하게 들려오는 소리에 위를 올려다보았다." << endl;
                cout << "“얼른 내손을 잡아!시간이 없어!”" << endl;
                cout << "다름아닌 “나”였다." << endl;
                cout << "어딘가 달라보이지만 “나”임에 틀림없었다." << endl;
                cout << "이 상황을 이해하기도 전 직감적으로 느낄 수 있었다." << endl;
                cout << "그곳만이 유일하게 탈출할 수 있는 방법이라는것을." << endl;
                cout << "한치의 망설임도 없이 비슷한 듯 다른 “나”의 손을 잡았다." << endl;
                cout << "그곳에 어떤 위험이 도사리는지도 모르는체...." << endl;
                cout << "END......?" << endl;
                cout << "===================================================================================" << endl;
                exit(0);
                break;
           
            
            default:
                break;
            }
        }
    }
};

#endif