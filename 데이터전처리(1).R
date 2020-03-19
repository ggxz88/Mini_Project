# 라이브러리 불러오기
install.packages("dplyr")
library(dplyr)

# 필요한 열(변수) 추출
subway_202002 <- subway_202002 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_202002

subway_202001_ <- subway_202001_ %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201912_ <- subway_201912_ %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201911_ <- subway_201911_ %>% select(사용일자, 호선명, 역명, 승차총승객수, 하차총승객수)

subway_201910 <- subway_201910 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201909 <- subway_201909 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201908 <- subway_201908 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201907 <- subway_201907 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201906 <- subway_201906 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201905 <- subway_201905 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201904 <- subway_201904 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201903 <- subway_201903 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201902 <- subway_201902 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201901 <- subway_201901 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201812 <- subway_201812 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201811 <- subway_201811 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201810 <- subway_201810 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201809 <- subway_201809 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201808 <- subway_201808 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201807 <- subway_201807 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201806 <- subway_201806 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201805 <- subway_201805 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201804 <- subway_201804 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201803 <- subway_201803 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201802 <- subway_201802 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)
subway_201801 <- subway_201801 %>% select(사용일자, 노선명, 역명, 승차총승객수, 하차총승객수)

# 변수명 변경
subway_201911_ <- rename(subway_201911_, 노선명 = 호선명)

# 데이터 합치기
subway_month1 <- bind_rows(subway_201801, subway_201802, subway_201803, subway_201804, subway_201805, subway_201806, subway_201807, subway_201808, subway_201809, subway_201810, subway_201811, subway_201812)

subway_month2 <- bind_rows(subway_201901, subway_201902, subway_201903, subway_201904, subway_201905, subway_201906, subway_201907, subway_201908)

subway_month3 <- bind_rows(subway_201909, subway_201910, subway_201911_, subway_201912_, subway_202001_, subway_202002)


# 결측치 확인
table(is.na(subway_month1))
table(is.na(subway_month2))
table(is.na(subway_month3))

# 데이터 합치기
subway_month <- bind_rows(subway_month1, subway_month2, subway_month3)


# 결측치 확인
table(is.na(subway_month))

# 노선별로 평균(이용객 수가 많은 호선 15개 골라내기)
subway_line <- subway_month %>%
  group_by(노선명) %>%
  summarise(승차총승객수평균 = mean(승차총승객수),
                    하차총승객수평균 = mean(하차총승객수))

s1 <- subway_line %>% arrange(승차총승객수평균) %>% head(11)
s1
s2 <- subway_line %>% arrange(하차총승객수평균) %>% head(11)
s2
s3 <- bind_rows(s1, s2)

table(s3$노선명)

# 필요한 행 추출
subway_month <- subway_month %>%
  filter(노선명 %in% c("과천선", "일산선", "안산선", "분당선", "경인선", "경부선","9호선", "8호선", "7호선", "6호선", "5호선", "4호선", "3호선", "2호선", "1호선"))

str(subway_month)

# 이상치 확인 후 NA로 변경
View(subway_month)

subway_month$하차총승객수 <- ifelse(subway_month$하차총승객수 == 0, NA, subway_month$하차총승객수)
subway_month$승차총승객수 <- ifelse(subway_month$하차총승객수 == 0, NA, subway_month$승차총승객수)

# 이상치 변경을 위한 노선, 역별 평균
subway_mean = subway_month %>%
  group_by(노선명,역명) %>%
  summarise(승차총승객수평균 = mean(승차총승객수, na.rm = T),
                    하차총승객수평균 = mean(하차총승객수, na.rm = T))

# 판단에 의한 이상치 제거 이유:메모장
subway_month <- subway_month %>% filter(!is.na(subway_month$승차총승객수))
table(is.na(subway_month))

#
subway_1 <- subway_month %>%
  group_by(노선명, 역명) %>%
  summarise(승차총승객수평균 = mean(승차총승객수),
                    하차총승객수평균 = mean(하차총승객수))

#subway_1 <- subway_month %>%
#  group_by(노선명, 역명) %>%
#  summarise(승차총승객수평균 = mean(승차총승객수),
#                    하차총승객수평균 = mean(하차총승객수))%>%
#  ungroup() %>%
#  select(-노선명)

#station <- subway_month %>%
#  select(노선명, 역명) %>%
#  filter(노선명 %in% c("과천선", "일산선", "안산선", "분당선", "경인선", "경부선", "9호선2단계","9호선", #"8호선", "7호선", "6호선", "5호선", "4호선", "3호선", "2호선", "1호선"))

#station <- distinct(station)

#subway_1 <- left_join(station, subway_station, by = "역명")

# 승차수/하차수 비율 -> 승차 수 보다 하차 수가 더 적으면 혼잡도가 덜 할것으로 판단
subway_1 <- subway_1  %>%
  mutate(ratio = 승차총승객수평균/하차총승객수평균)

#subway_1 <- rename(subway_1, ratio = total)

#subway_1 <- subway_1 %>% select(-ratio_)

subway_1 %>% arrange(ratio) %>%
  head(20)

subway_1 %>% arrange(desc(ratio)) %>%
  head(20)

#subway_total <- subway_1 %>%
#  ungroup()

#subway_total <- subway_total %>%
#  group_by(노선명, 역명) %>%
#  arrange(subway_total$ratio)


