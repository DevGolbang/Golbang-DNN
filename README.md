# C++ Neural Network
배열, 리스트로 만든 단순한 NN 구현 목표
 
# Solved Issues
1. Memory Leak 
2. Ensure Object Independence
3. CleanUp-Code
5. Iteration Optimized

# To Change
1. 깊은복사 최대한 배제하고 쓸데없는 Heap사용 최대한 배제하기
2. O(n^2)부분 최대한 배제하기
3. 멀티스레딩으로 교체(앞먹임 기준으로 테스트중) -> 성능 2000배 느려짐(스레딩 객체 다수생성 및 삭제) -> 스레드풀링 사용(소스 퍼와서 성능 튜닝중)
4. C스타일로 구성하기 어려운 경우 Iteration Trick 과 같은 트릭으로 최대한 Performance 손상 배제하기

# To Add
1. Bias Back Propogation 추가
2. CNN 할 수 있게 개조 -> RNN(LTMS)도 추가
3. Input 제어하는 모듈 추가(.csv, .png 파일 파싱) -> .png사용시 자동으로 CNN 변환
4. CUDA Version 시작(CUDA Environment 구축 및 예제 테스트(학습))
