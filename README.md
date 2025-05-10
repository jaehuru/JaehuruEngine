# 자체 엔진 만들어보기
자체 엔진을 만들어보며 게임 엔진에 대하여 깊게 알아가보자 유튜브를 통해 깊게 학습해 보기위해 만든 프로젝트이다.
클라이언트 개발자라면 렌더링 파이프라인같은 핵심 그래픽스 기술을 알아야 한다고 생각했기 때문이다.

## step1. WinAPI 이해하기
1. WinMain의 코드흐름을 파악
2. DC 정의와 스톡 오브젝트
3. PeekMessage
4. 정적 라이브러리와 동적 라이브러리 장단점
5. Application 클래스 구현
6. 매 프레임마다 도형을 찍어보고 이동 PeekMessage + Application::Run()
7. GameObject 클래스 구현
8. DeltaTime은 프레임 간 시간 차이를 의미하며, 이를 통해 컴퓨터 사양(성능)에 따라 달라지는 실행 속도를 보정
9. 더블 버퍼링의 원리 학습
10. Scene, SceneManager 클라스 구현
11. Component 구조
12. 2D vector 구현
13. Gdiplus로 배경화면 띄우기
14. Scene의 Enter() Exit() 함수 구현
15. Layer 구조를 보고 화면 출력 순서를 파악
16. 오브젝트를 생성을 위한 Instantiate함수 구현
17. Resource 클래스 구현
18. Script 클래스 구현
19. Camera Component 클래스 구현
20. Animator, Animation 클래스 구현과 AlphaBlend 함수 사용해보기