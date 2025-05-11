# 프로젝트 소개
이 프로젝트는 자체 게임 엔진을 개발하며 3D 그래픽스 렌더링과 게임 엔진 아키텍처의 근본 원리를 학습하기 위한 목적으로 시작되었습니다.
Windows 기반에서의 기초적인 윈도우 창 생성과 메시지 루프 처리부터 시작하여, DirectX 11 기반의 렌더링 파이프라인을 직접 구현하며, 이후 실제 게임 제작까지 확장해 나갈 예정입니다.

## step1. WinAPI 기반 아키텍처 및 기본 렌더링 구조 학습
1. WinMain 진입점 및 메시지 루프 처리 흐름 이해
2. Device Context(DC) 및 스톡 오브젝트 사용법 학습
3. PeekMessage 기반의 논블로킹 메시지 루프 구현
4. 정적/동적 라이브러리의 차이와 활용
5. Application 클래스 설계 및 루프 관리 구조 도입
6. 도형 렌더링 및 이동 구현을 통한 프레임 기반 구조 이해
7. GameObject 기반의 오브젝트 추상화 구조 설계
8. DeltaTime을 통한 성능 독립적 시간 처리
9. 더블 버퍼링의 원리 및 flickering 방지 기법 적용
10. Scene 및 SceneManager 클래스 구현을 통한 씬 전환 구조 구축
11. Component 기반 아키텍처 도입 (Entity-Component 구조)
12. 2D Vector 클래스 직접 구현 및 연산 처리
13. GDI+를 통한 이미지 렌더링 및 배경 출력
14. Scene 전환 시 상태 제어용 Enter(), Exit() 함수 구현
15. Layer 구조 설계로 오브젝트 렌더링 순서 제어
16. 오브젝트 동적 생성을 위한 Instantiate 함수 구현
17. Resource 관리 시스템 구현 (텍스처 등)
18. Script 클래스 도입으로 사용자 정의 동작 처리
19. Camera Component 구현 및 뷰 변환 처리 도입
20. Animator 및 Animation 클래스 구현 + AlphaBlend 테스트
21. Transform을 통한 Position, Rotation, Scale 통합 관리 구조 도입
22. 픽셀 투명화 처리 및 알파 블렌딩 구현
23. 상태 기반 FSM 패턴 적용으로 객체 행동 제어
24. FSM 패턴을 활용한 간단한 AI 행동 로직을 구성
25. 포인터 함수를 이용한 애니메이션 이벤트 시스템 구현
26. Memory Leak 체크를 위한 _CrtSetDbgFlag() 함수를 활용
27. 카메라 타겟팅 설정
28. 게임 오브젝트의 활성 상태를 동적으로 제어하기 위한 SetActive() 함수 구현
29. Destroy() 함수를 통해 프로그램 실행 중 Scene에서 게임 오브젝트를 제거
30. 애니메이션 리소스가 저장된 폴더 경로를 기반으로, 프레임 이미지들을 자동으로 로드하여 애니메이션 클립을 생성하는 기능을 제공하는 CreateAnimationByFolder() 함수 구현
31. BMP 이미지가 32비트 알파 채널을 포함하는지 여부에 따라 알파 블렌딩 처리(Alpha Blending) 또는 일반 비트 블리트((BitBlt: Bit Block Transfer)) 처리를 자동으로 분기