/* 
  파일이름: main.c
  작 성 자: 주아름 / 60252584
  하 는 일: 초보 편의점 알바생을 위한 기초 POS 결제 시스템 (V1.0)
*/

#include <stdio.h>

int main()
{
  // 1. 변수 선언 (기존 변수 + 2차 추가 변수)
  char itemName[20];    // 상품명 (문자열)
  int Price;            // 상품 가격 (정수)
  int count;            // 판매 수량 (정수)
  int pay;              // 손님에게 받은 돈 (정수)
  int total;            // 총 결제 금액 (정수)
  double taxRate = 0.1; // 부가세율 10% (실수)

  // [2차 추가 변수]
  int itemType;         // 1: 도시락, 2: 주류, 3: 일반
  int hour;             // 폐기 확인용 시간
  int age;              // 성인 인증용 나이
  int bagChoice;        // 봉투 유무

  printf("========= GS25 편의점 POS 시스템 V1.0 =========\n");
  printf("신입 알바생님, 환영합니다! 계산을 시작합니다.\n\n");

  // 2. 입력 및 분류
  printf("0. 상품 종류 선택 (1: 도시락, 2: 주류, 3: 기타): ");
  scanf("%d", &itemType);

  printf("1. 판매할 상품명 입력: ");
  scanf("%s", &itmeName);

  // [분류 로직: 폐기 및 성인인증 체크]
  if (itemType == 1){
    printf("  > 현재 시간 입력(0-23): ");
    scanf("%d", &hour);
    if (hour >= 22){
      printf("\n [판매 중단] 22시 경과 폐기 상품입니다!\n");
      return 0;
    }
  }
  else if (itemyType == 2) {
    printf("  > 구매자 나이 입력: ");
    scanf("%d", &age);
    if (age <20) {
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
    printf("  (봉투값 100원이 추가되었습니다.) \n");
  }

  // 4. 결과 출력
  printf("\n----------------------------------------------\n");
  printf("상품명: %s\n", itemName);
  printf("총 결제 금액: %d원 (부가세 포함)\n", total);
  printf("----------------------------------------------\n");

  // 5. 거스름돈 계산을 위한 추가 입력 및 잔액 확인
  printf("손님에게 받은 금액을 입력하세요: ");
  scanf("%d", &pay);

  if (pay >= total) {
    printf("\n>>> 거스름돈: %d원입니다.\n", pay - total);
    printf("==============================================\n");
    printf("결제가 완료되었습니다. 오늘도 화이팅하세요!\n");
  }
  else {
    printf("\n [결제 실패] 금액이 %d원 부족합니다!\n", total - pay);
    printf("==============================================\n");
  }
  
return 0;
}
