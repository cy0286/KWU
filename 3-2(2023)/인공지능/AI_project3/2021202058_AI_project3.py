#!/usr/bin/env python
# coding: utf-8

# In[1]:


import numpy as np


# In[2]:


# 7x7 크기의 grid 생성 및 모든 값 -1로 초기화
grid_world = -1 * np.ones((7, 7), dtype=int)

# 시작점과 끝점 설정
start_point = (0, 0)
end_point = (6, 6)

# 시작점과 끝점에 각각 0 할당
grid_world[start_point] = -200
grid_world[end_point] = 0

# -100 할당
temp = [(0, 2), (1, 2), (3, 4), (3, 5), (6, 2), (6, 3)]


for coord in temp:
    if 0 <= coord[0] < 7 and 0 <= coord[1] < 7:
        grid_world[coord] = -100
        
print(grid_world)


# In[3]:


available_actions = ['Up', 'Down', 'Left', 'Right']

def cal_direc(value_matrix):
     # 최적 행동을 저장할 배열 초기화
    optimal_actions = np.empty((7, 7), dtype='object')

    for i in range(7):
        for j in range(7):
            if (i, j) in [(6, 6)]:
                optimal_actions[i, j] = [0]  # 끝점의 경우 움직일 필요가 없으므로 0으로 초기화
            else:
                # 가능한 움직임을 정의
                possible_moves = [(max(0, i-1), j), (min(6, i+1), j), (i, max(0, j-1)), (i, min(6, j+1))]
                # 가능한 움직임 중 가장 높은 가치를 찾음
                max_value = max(value_matrix[a, b] for a, b in possible_moves)
                # 가장 높은 가치를 갖는 행동들을 찾음
                best_actions = [available_actions[k] for k, (a, b) in enumerate(possible_moves) if value_matrix[a, b] == max_value]
                
                # 특정 위치에서 움직일 수 없는 경우 해당 방향을 제외
                if i == 0 and 'Up' in best_actions:
                    best_actions.remove('Up')
                elif i == 6 and 'Down' in best_actions:
                    best_actions.remove('Down')
                elif j == 0 and 'Left' in best_actions:
                    best_actions.remove('Left')
                elif j == 6 and 'Right' in best_actions:
                    best_actions.remove('Right')

                 # 최적 행동 배열에 결과 저장
                optimal_actions[i, j] = best_actions

    return optimal_actions


# In[4]:


def policy_evaluation(grid_world, iterations=2000):
    state = grid_world.shape
    prev_state = np.zeros(state)
    next_state = np.zeros(state)

    for i in range(iterations):
        for j in range(state[0]):
            for z in range(state[1]):
                 # 끝점은 건너뜀
                if (j == state[0] - 1 and z == state[1] - 1):
                    continue
                
                # 주변 값을 가져와 현재 위치 값 업데이트
                up_value = grid_world[j, z] + prev_state[j-1, z] if j > 0 else grid_world[j, z] + prev_state[j, z]
                down_value = grid_world[j, z] + prev_state[j+1, z] if j < state[0] - 1 else grid_world[j, z] + prev_state[j, z]
                left_value = grid_world[j, z] + prev_state[j, z-1] if z > 0 else grid_world[j, z] + prev_state[j, z]
                right_value = grid_world[j, z] + prev_state[j, z+1] if z < state[1] - 1 else grid_world[j, z] + prev_state[j, z]

                 # 주변 값의 평균을 계산해 현재 위치 값 업데이트
                value = 0.25 * (up_value + down_value + left_value + right_value)
                next_state[j, z] = value

        print("Iteration {}: \n{}".format(i, prev_state))
        prev_state = np.round(next_state, decimals=1)

    print("Final Result (Iteration {}): \n{}".format(iterations, prev_state))
    direct = cal_direc(prev_state)
    print(direct)
policy_evaluation(grid_world)


# In[5]:


def policy_improvement(grid_world, iterations=20):
    state = grid_world.shape
    prev_state = np.zeros(state)
    next_state = np.zeros(state)

    # 주어진 반복 횟수 동안 정책을 개선
    for i in range(iterations):
        for j in range(state[0]):
            for z in range(state[1]):
                # 끝점은 건너뜀
                if (j == state[0] - 1 and z == state[1] - 1):
                    continue

                 # 현재 정책에 따라 최적 행동을 계산
                result_directions = cal_direc(prev_state)

                # 움직일 수 없는 위치는 무시
                if '0' in result_directions[j, z] or not result_directions[j, z]:
                    continue
                    
                ratio = 1.0 / len(result_directions[j, z])
                value = 0.0

                 # 각 방향에 따라 이동한 위치에서의 가치를 더함
                for direction in result_directions[j, z]:
                    row, col = j, z

                    if direction == 'Up' and j > 0:
                        row -= 1
                    elif direction == 'Down' and j < state[0] - 1:
                        row += 1
                    elif direction == 'Left' and z > 0:
                        col -= 1
                    elif direction == 'Right' and z < state[1] - 1:
                        col += 1

                    value += ratio * (grid_world[j, z] + prev_state[row, col])

                next_state[j, z] = value
        
        if i == 0:
            direct = cal_direc(prev_state)
            print("Iteration 0: \n{}".format(prev_state))
            print(direct)
        else:
            print("Iteration {}: \n{}".format(i, next_state))
            prev_state = np.round(next_state, decimals=1)
            direct = cal_direc(prev_state)
            print(direct)
            
    print("Final Result (Iteration {}): \n{}".format(iterations, prev_state))
    direct = cal_direc(prev_state)
    print(direct)

policy_improvement(grid_world)


# In[6]:


def value_iteration(grid_world, iterations=20):
    state = grid_world.shape
    prev_state = np.zeros(state)
    next_state = np.zeros(state)

    for i in range(iterations):
        for j in range(state[0]):
            for z in range(state[1]):
                 # 끝점은 건너뜀
                if (j == state[0] - 1 and z == state[1] - 1):
                    continue
                
                # 주변 값을 가져와 현재 위치 값 업데이트
                up_value = grid_world[j, z] + prev_state[j-1, z] if j > 0 else grid_world[j, z] + prev_state[j, z]
                down_value = grid_world[j, z] + prev_state[j+1, z] if j < state[0] - 1 else grid_world[j, z] + prev_state[j, z]
                left_value = grid_world[j, z] + prev_state[j, z-1] if z > 0 else grid_world[j, z] + prev_state[j, z]
                right_value = grid_world[j, z] + prev_state[j, z+1] if z < state[1] - 1 else grid_world[j, z] + prev_state[j, z]
                
                 # 네 방향 중 최댓값 선택
                value = max(up_value, down_value, left_value, right_value)
                next_state[j, z] = value

        print("Iteration {}: \n{}".format(i, prev_state))
        prev_state = np.round(next_state, decimals=1)

    print("Final Result (Iteration {}): \n{}".format(iterations, prev_state))
value_iteration(grid_world)

