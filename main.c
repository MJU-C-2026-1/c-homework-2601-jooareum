/* 
  파일이름: main.c
  작 성 자: 주아름 / 60252584
  하 는 일: 초보 편의점 알바생을 위한 기초 POS 결제 시스템
*/
 
#include <stdio.h>

// 전역 변수 선언 (누적 데이터 관리)
int totalSales = 0;     // 당일 총 매출액
int totalCount = 0;     // 오늘 판매된 총 상품 개수

// 함수 선언
void showMenu();
int processPayment(int itemType);
void showSalesStatus();

int main()
{
	
  int menuChoice;
  int itemType;
  int paymentResult;

  printf("========= GS25 편의점 POS 시스템 V3.0 =========\n");
  printf("신입 알바생님, 환영합니다! 계산을 시작합니다.\n\n");

  // 무한 루프 시작
  while(1)
  {
    showMenu();
    printf("실행할 메뉴 번호를 선택하세요: ");

    scanf(" %d", &menuChoice);

    if(menuChoice == 1)
    {
      printf("\n[상품 결제 및 입력 진입]\n");
      printf("1. 상품 카테고리(1: 도시락, 2: 주류, 3: 일반):");
      scanf("%d", &itemType);

      // 결제 처리 함수 호출
      paymentResult = processPayment(itemType);

      if(paymentResult > 0)
      {
        printf("\n=> 정상적으로 결제가 완료되어 메인 메뉴로 돌아갑니다. \n");
      }
      else
      {
        printf("\n=> 결제가 완료되지 않아 메인 메뉴로 돌아갑니다. \n");
      }
    }
    else if(menuChoice == 2)
    {
      // 누적 매출 함수 호출
      showSalesStatus();
    }
    else if(menuChoice == 3)
    {
      // 프로그램 종료
      printf("\n==============================================\n");
      printf("오늘 하루도 수고하셨습니다. 정산을 마감하고 POS를 종료합니다.\n");
      showSalesStatus();
      break;
    }
    else
    {
      printf("올바른 메뉴 번호가 아닙니다. 다시 선택해주세요.\n");
    }
    printf("\n");
  }
  return 0;
}

// 메인 메뉴 출력 함수
void showMenu()
{
  printf("\n-------------------------------\n");
  printf("        [POS 메인 메뉴]        \n");
  printf("-------------------------------\n");
  printf(" 1. 상품 입력 및 결제\n");
  printf(" 2. 당일 누적 매출 조회\n");
  printf(" 3. 영업 마감 및 시스템 종료\n");
  printf("-------------------------------\n");
}

// 결제 처리 함수
int processPayment(int itemType)
{
  // 1. 변수 선언 (기본 변수 + 2차 추가 변수)
  char itemName[20];    // 상품명 (문자열)
  int Price;            // 상품 가격 (정수)
  int count;            // 판매 수량 (정수)
  int pay;              // 손님에게 받은 돈 (정수)
  int total;            // 총 결제 금액 (정수)
  double taxRate = 0.1; // 부가세율 10% (실수)

  int hour;             // 폐기 확인용 시간
  int age;              // 성인 인증용 나이
  int bagChoice;        // 봉투 유무

  // 2. 입력 및 분류
  printf("1. 판매할 상품명 입력: ");
  scanf("%s", itemName);

  // [분류 로직: 폐기 및 성인인증 체크]
  if (itemType == 1) {
    printf("  > 현재 시간 입력(0-23): ");
    scanf("%d", &hour);
    if(hour >= 22) {
      printf("\n [판매 중단] 22시 경과 폐기 상품입니다!\n");
      return 0;
    }
  }
  else if (itemType == 2) {
    printf("  > 구매자 나이 입력: ");
    scanf("%d", &age);
    if(age < 20) {
      printf("\n [판매 중단] 미성년자에게 판매할 수 없습니다!\n");
      return 0;
    }
  }

  printf("2. 상품 단가 입력(원): ");
  scanf("%d", &Price);

  printf("3. 판매 수량 입력(개): ");
  scanf("%d", &count);

  // 3. 산술 연산 (가격 * 수량 + 봉투값)
  total = Price * count;

  printf("4. 비닐봉투가 필요합니까? (1: 예, 0: 아니오): ");
  scanf("%d", &bagChoice);
  if (bagChoice == 1) {
    total += 100;
    printf("  (봉투값 100원이 추가되었습니다.)\n");
  }

  // 4. 결과 출력
  printf("\n----------------------------------------------\n");
  printf("상품명: %s\n", itemName);
  printf("총 결제 금액: %d원 (부가세 포함)\n", total);
  printf("----------------------------------------------\n");

  // 5. 거스름돈 계산을 위한 추가 입력
  printf("손님에게 받은 금액을 입력하세요: ");
  scanf("%d", &pay);

  if (pay >= total) {
    printf("\n>>> 거스름돈: %d원입니다.\n", pay - total);
    printf("==============================================\n");
    printf("결제가 완료되었습니다. 오늘도 화이팅하세요!\n");

    // 전역 변수에 당일 매출 및 수량 누적
    totalSales += total;
    totalCount += count;
    return total;
  }
  else {
    printf("\n [결제 실패] 금액이 %d원 부족합니다!\n", total - pay);
    printf("==============================================\n");
    return 0;
  }
}

// 당일 누적 매출 조회 함수
void showSalesStatus()
{
  printf("\n ------ [당일 누적 매출 현황] ------\n");
  printf(" > 오늘 판매된 총 상품 개수: %d개\n", totalCount);
  printf(" > 현재까지 누적된 총 매출액: %d원\n", totalSales);
  printf("-------------------------------------\n");
}
