library(dplyr)

str(subway_time)

# 필요한 행 추출
subway_time <- subway_time %>%
  filter(사용월 %in% c(202002, 202001, 201912, 201911, 201910, 201909, 201908, 201907, 201906, 201905, 201904, 201903, 201902, 201901, 201812, 201811, 201810, 201809, 201808, 201807, 201806, 201805, 201804, 201803, 201802, 201801))


subway_time <- subway_time %>%
  filter(호선명 %in% c("과천선", "일산선", "안산선", "분당선", "경인선", "경부선","9호선", "8호선", "7호선", "6호선", "5호선", "4호선", "3호선", "2호선", "1호선")) %>%
  select("사용월", "호선명", "지하철역", "X06시.07시.승차인원", "X06시.07시.하차인원", "X07시.08시.승차인원", "X07시.08시.하차인원", "X08시.09시.승차인원", "X08시.09시.하차인원", "X17시.18시.승차인원", "X17시.18시.하차인원", "X18시.19시.승차인원", "X18시.19시.하차인원", "X19시.20시.승차인원", "X19시.20시.하차인원")

# 결측치 확인
table(is.na(subway_time))

# 이상치 확인
subway_time %>% arrange(X06시.07시.하차인원) %>% head()


# 판단에 의한 이상치 제거 이유:메모장
subway_time <- subway_time[!(subway_time$호선명 == "분당선" & subway_time$지하철역 == "복정"),]
subway_time <- subway_time[!(subway_time$호선명 == "3호선" & subway_time$지하철역 == "충무로"),]
subway_time <- subway_time[!(subway_time$호선명 == "6호선" & subway_time$지하철역 == "연신내"),]
subway_time <- subway_time[!(subway_time$호선명 == "6호선" & subway_time$지하철역 == "신내"),]
subway_time <- subway_time[!(subway_time$호선명 == "일산선" & subway_time$지하철역 == "지축"),]

#
subway_time <-  subway_time %>%
  group_by(호선명, 지하철역) %>%
  summarise(X06시.07시.승차인원평균 = mean(X06시.07시.승차인원),
            X06시.07시.하차인원평균 = mean(X06시.07시.하차인원),
            X07시.08시.승차인원평균 = mean(X07시.08시.승차인원),
            X07시.08시.하차인원평균 = mean(X07시.08시.하차인원),
            X08시.09시.승차인원평균 = mean(X08시.09시.승차인원),
            X08시.09시.하차인원평균 = mean(X08시.09시.하차인원),
            X17시.18시.승차인원평균 = mean(X17시.18시.승차인원),
            X17시.18시.하차인원평균 = mean(X17시.18시.하차인원),
            X18시.19시.승차인원평균 = mean(X18시.19시.승차인원),
            X18시.19시.하차인원평균 = mean(X18시.19시.하차인원),
            X19시.20시.승차인원평균 = mean(X19시.20시.승차인원),
            X19시.20시.하차인원평균 = mean(X19시.20시.하차인원))

#subway_time <-  subway_time %>%
#  group_by(호선명, 지하철역) %>%
#  summarise(X06시.07시.승차인원평균 = mean(X06시.07시.승차인원),
#            X06시.07시.하차인원평균 = mean(X06시.07시.하차인원),
#            X07시.08시.승차인원평균 = mean(X07시.08시.승차인원),
#            X07시.08시.하차인원평균 = mean(X07시.08시.하차인원),
#            X08시.09시.승차인원평균 = mean(X08시.09시.승차인원),
#            X08시.09시.하차인원평균 = mean(X08시.09시.하차인원),
#            X17시.18시.승차인원평균 = mean(X17시.18시.승차인원),
#            X17시.18시.하차인원평균 = mean(X17시.18시.하차인원),
#            X18시.19시.승차인원평균 = mean(X18시.19시.승차인원),
#            X18시.19시.하차인원평균 = mean(X18시.19시.하차인원),
#            X19시.20시.승차인원평균 = mean(X19시.20시.승차인원),
#            X19시.20시.하차인원평균 = mean(X19시.20시.하차인원)) %>%
#  ungroup() %>%
#  select(-호선명)

#test9 <- subway_time %>% select(-노선명)


# 변수명 변경
subway_time <- rename(subway_time, 노선명 = 호선명)
subway_time <- rename(subway_time, 역명 = 지하철역)

#
#subway <- left_join(subway_1, subway_time, by = "역명")

#subway <- distinct(subway)

# 승차수/하차수 비율
subway_time <- subway_time %>%
  mutate(X06시.07시_ratio = X06시.07시.승차인원평균/X06시.07시.하차인원평균) %>%
  mutate(X07시.08시_ratio = X07시.08시.승차인원평균/X07시.08시.하차인원평균) %>%
  mutate(X08시.09시_ratio = X08시.09시.승차인원평균/X08시.09시.하차인원평균) %>%
  mutate(X17시.18시_ratio = X17시.18시.승차인원평균/X17시.18시.하차인원평균) %>%
  mutate(X18시.19시_ratio = X18시.19시.승차인원평균/X18시.19시.하차인원평균) %>%
  mutate(X19시.20시_ratio = X19시.20시.승차인원평균/X19시.20시.하차인원평균)

subway_2 <- subway_time %>% select(노선명, 역명, X06시.07시_ratio, X07시.08시_ratio, X08시.09시_ratio, X17시.18시_ratio, X18시.19시_ratio, X19시.20시_ratio)


