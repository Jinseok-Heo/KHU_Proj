import pandas as pd
import numpy as np
import os

cwd = os.getcwd()
file_path = os.path.join(cwd, 'raw_data.txt')

with open(file_path, encoding='utf-8') as file:
    data = file.read()
    data = data.replace('\n', '')
    data = data.split('조회')

numbers = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9']
def time_processing(time):
    bar_idx = time.find('-')
    start_time = time[:bar_idx]
    if time[bar_idx + 1] not in numbers:
        end_time = np.NaN
    else:
        end_time = time[bar_idx + 1:]
    return start_time, end_time

def line_processing(line):
    days = ['월', '화', '수', '목', '금', '토', '일']
    class_types = ['전공기초(11)', '전공선택(05)', '전공필수(04)', '교직전선(20)', '기초교과(16)', '중핵교과(14)', '배분이수(15)', '자유이수(17)', '자유선택(08)', '교직과(06)']
    ret = {}
    ret['class_code'] = np.NaN
    ret['class_name'] = np.NaN
    ret['professor_name'] = np.NaN
    ret['date'] = []
    ret['start_time'] = []
    ret['end_time'] = []
    ret['class_type'] = np.NaN
    
    commaidx = line.find(',')
    slashidx = line.find('/')
    for c_type in class_types:
        typeidx = line.find(c_type)
        if typeidx != -1:
            ret['class_type'] = c_type
            break
    if typeidx == -1:
        ret['class_type'] = np.NaN
    idxs = list(filter(lambda x: line[x] == '-', range(len(line))))    # indexes of '-'
    bar_idx = idxs[1]
    for idx in idxs:
        if (idx >= 7 and line[idx - 7] in days) or (idx >= 2 and line[idx - 2] in days):
            bar_idx = idx
            break

    for i, idx in enumerate(idxs):
        if i == 0: #Class_code
            if line[idx + 1] == 'G': #G00
                ret['class_code'] = line[:idx + 4]
                if commaidx != -1 and commaidx < bar_idx:
                    if slashidx == -1 or slashidx >= bar_idx - 7:
                        ret['class_name'] = line[idx + 4:commaidx]
                        ret['professor_name'] = line[commaidx + 1:bar_idx - 8]  
                    elif slashidx < bar_idx - 7:
                        ret['class_name'] = line[idx + 4:commaidx]
                        if line[slashidx + 2] != '.':
                            if bar_idx - 6 != slashidx:
                                ret['professor_name'] = line[commaidx + 1:bar_idx - 8].replace(' / ', ', ')
                            else:
                                ret['professor_name'] = line[commaidx + 1:bar_idx - 1].replace(' / ', ', ')
                elif slashidx != -1 and slashidx < bar_idx - 7:    #/ ..
                    ret['class_name'] = line[idx + 4:slashidx - 4]
                    if line[slashidx + 2] != '.':
                        if line[slashidx + 5] == '/':
                            if line[slashidx + 9] in numbers:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:slashidx + 4] + ', ' + line[slashidx + 7:bar_idx - 8]
                            else:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:slashidx + 4] + ', ' + line[slashidx + 7:bar_idx - 8]
                        elif line[slashidx + 6] == '/':
                            if line[slashidx + 10] in numbers:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:slashidx + 5] + ', ' + line[slashidx + 8:bar_idx - 8]
                            else:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:slashidx + 5] + ', ' + line[slashidx + 8:bar_idx - 8]
                        else:
                            if line[slashidx + 4] in numbers:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:bar_idx - 8]
                            elif line[slashidx + 5] in numbers:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:bar_idx - 8]
                    else:
                        ret['professor_name'] = line[slashidx - 4:slashidx - 1]
                elif line[bar_idx - 7] in days:
                    ret['class_name'] = line[idx + 4:bar_idx - 11]
                    ret['professor_name'] = line[bar_idx - 11:bar_idx - 8]
                elif line[bar_idx - 1] in numbers or line[bar_idx - 1] in days:
                    ret['class_name'] = line[idx + 4:bar_idx - 4]
                    ret['professor_name'] = line[bar_idx - 4:bar_idx - 1]
                    
            else:
                ret['class_code'] = line[:idx + 3]
                if commaidx != -1 and commaidx < bar_idx:
                    if slashidx == -1 or slashidx >= bar_idx - 7:
                        ret['class_name'] = line[idx + 3:commaidx]
                        ret['professor_name'] = line[commaidx + 1:bar_idx - 8]  
                    elif slashidx < bar_idx - 7:
                        ret['class_name'] = line[idx + 3:commaidx]
                        if line[slashidx + 2] != '.':
                            ret['professor_name'] = line[commaidx + 1:bar_idx - 8].replace(' / ', ', ')
                elif slashidx != -1 and slashidx < bar_idx - 7:    #/ ..
                    ret['class_name'] = line[idx + 3:slashidx - 4]
                    if line[slashidx + 2] != '.':
                        if line[slashidx + 5] == '/':
                            if line[slashidx + 9] in numbers:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:slashidx + 4] + ', ' + line[slashidx + 7:bar_idx - 8]
                            else:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:slashidx + 4] + ', ' + line[slashidx + 7:bar_idx - 8]
                        elif line[slashidx + 6] == '/':
                            if line[slashidx + 10] in numbers:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:slashidx + 5] + ', ' + line[slashidx + 8:bar_idx - 8]
                            else:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:slashidx + 5] + ', ' + line[slashidx + 8:bar_idx - 8]
                        else:
                            if line[slashidx + 4] in numbers:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:bar_idx - 8]
                            elif line[slashidx + 5] in numbers:
                                ret['professor_name'] = line[slashidx - 4:slashidx - 1] + ', ' + line[slashidx + 2:bar_idx - 8]
                    else:
                        ret['professor_name'] = line[slashidx - 4:slashidx - 1]
                elif line[bar_idx - 7] in days:
                    ret['class_name'] = line[idx + 3:bar_idx - 11]
                    ret['professor_name'] = line[bar_idx - 11:bar_idx - 8]
                elif line[bar_idx - 1] in numbers:
                    if line[bar_idx - 3:bar_idx - 1] == '..':
                        ret['class_name'] = line[idx + 3:bar_idx - 3]
                        ret['professor_name'] = np.NaN
                    else:
                        ret['class_name'] = line[idx + 3:bar_idx - 4]
                        ret['professor_name'] = line[bar_idx - 4:bar_idx - 1]
                elif line[bar_idx - 1] in days:
                    ret['class_name'] = line[idx + 3:bar_idx - 5]
                    ret['professor_name'] = line[bar_idx - 5:bar_idx-2]
        else:
            if line[idx - 7] in days:
                ret['date'].append(line[idx - 7])
                start_time, end_time = time_processing(line[idx - 5:idx + 6])
                ret['start_time'].append(start_time)
                ret['end_time'].append(end_time)
                
            elif line[idx - 1] in days:
                ret['date'].append(line[idx - 1])
                ret['start_time'].append(np.NaN)
                ret['end_time'].append(np.NaN)
                
    if len(ret['date']) == 0 and len(ret['start_time']) == 0:
        ret['start_time'].append(np.NaN)
        ret['end_time'].append(np.NaN)
    return ret

from IPython.display import display
processed_datas = []
keys = ['date', 'start_time', 'end_time', 'class_type', 'class_name', 'professor_name']
df = pd.DataFrame(columns=keys)
for i, line in enumerate(data):
    processed_data = line_processing(line)
    for d, s_t, e_t in zip(processed_data['date'], processed_data['start_time'], processed_data['end_time']):
        df = df.append({
            'date' : d,
            'start_time' : s_t,
            'end_time' : e_t,
            'class_type' : processed_data['class_type'],
            'class_code' : processed_data['class_code'],
            'class_name' : processed_data['class_name'],
            'professor_name' : processed_data['professor_name']
        }, ignore_index=True)

d = df.drop_duplicates('class_name')
list(d['class_name'])

#df.to_csv('db_file.csv', encoding='utf-8-sig')