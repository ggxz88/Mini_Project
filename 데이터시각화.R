library(ggplot2)

install.packages("plotly")
library(plotly)

sixam_de = subway_2 %>% arrange(desc(X06시.07시_ratio)) %>%
  select(노선명, 역명, X06시.07시_ratio) %>%
  head(10)

p1 <- ggplot(data = sixam_de, aes(x = 노선명, y = X06시.07시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p1
ggplotly(p1)

sixam_as = subway_2 %>% arrange(X06시.07시_ratio) %>%
  select(노선명, 역명, X06시.07시_ratio) %>%
  head(10)

p2 <- ggplot(data = sixam_as, aes(x = 노선명, y = X06시.07시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p2
ggplotly(p2)

sevenam_de = subway_2 %>% arrange(desc(X07시.08시_ratio)) %>%
  select(노선명, 역명, X07시.08시_ratio) %>%
  head(10)

p3 <- ggplot(data = sevenam_de, aes(x = 노선명, y = X07시.08시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p3
ggplotly(p3)

sevenam_as = subway_2 %>% arrange(X07시.08시_ratio) %>%
  select(노선명, 역명, X07시.08시_ratio) %>%
  head(10)

p4 <- ggplot(data = sevenam_as, aes(x = 노선명, y = X07시.08시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p4
ggplotly(p3)

eightam_de = subway_2 %>% arrange(desc(X08시.09시_ratio)) %>%
  select(노선명, 역명, X08시.09시_ratio) %>%
  head(10)

p5 <- ggplot(data = eightam_de, aes(x = 노선명, y = X08시.09시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p5
ggplotly(p4)

eightam_as = subway_2 %>% arrange(X08시.09시_ratio) %>%
  select(노선명, 역명, X08시.09시_ratio) %>%
  head(10)

p6 <- ggplot(data = eightam_as, aes(x = 노선명, y = X08시.09시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p6
ggplotly(p6)

fivepm_de = subway_2 %>% arrange(desc(X17시.18시_ratio)) %>%
  select(노선명, 역명, X17시.18시_ratio) %>%
  head(10)

p7 <- ggplot(data = fivepm_de, aes(x = 노선명, y = X17시.18시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p7
ggplotly(p7)

fivepm_as = subway_2 %>% arrange(X17시.18시_ratio) %>%
  select(노선명, 역명, X17시.18시_ratio) %>%
  head(10)

p8 <- ggplot(data = fivepm_as, aes(x = 노선명, y = X17시.18시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p8
ggplotly(p8)

sixpm_de = subway_2 %>% arrange(desc(X18시.19시_ratio)) %>%
  select(노선명, 역명, X18시.19시_ratio) %>%
  head(10)

p9 <- ggplot(data = sixpm_de, aes(x = 노선명, y = X18시.19시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p9
ggplotly(p9)

sixpm_as = subway_2 %>% arrange(X18시.19시_ratio) %>%
  select(노선명, 역명, X18시.19시_ratio) %>%
  head(10)

p10 <- ggplot(data = sixpm_as, aes(x = 노선명, y = X18시.19시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p10
ggplotly(p10)

sevenpm_de = subway_2 %>% arrange(desc(X19시.20시_ratio)) %>%
  select(노선명, 역명, X19시.20시_ratio) %>%
  head(10)

p11 <- ggplot(data = sevenpm_de, aes(x = 노선명, y = X19시.20시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p11
ggplotly(p11)

sevenpm_as = subway_2 %>% arrange(X19시.20시_ratio) %>%
  select(노선명, 역명, X19시.20시_ratio) %>%
  head(10)

p12 <- ggplot(data = sevenpm_as, aes(x = 노선명, y = X19시.20시_ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p12
ggplotly(p12)

total_de <- subway_1 %>% arrange(desc(ratio)) %>%
  select(노선명, 역명, ratio) %>%
  head(10)

p13 <- ggplot(data = total_de, aes(x = 노선명, y = ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip()
p13
ggplotly(p13)

total_as <- subway_1 %>% arrange(ratio) %>%
  select(노선명, 역명, ratio) %>%
  head(10)

p14 <- ggplot(data = total_as, aes(x = 노선명, y = ratio, fill = 역명)) + geom_col(position = "dodge") + coord_flip() + ylim(0, 1)
p14
ggplotly(p14)

gotowork_de <- bind_rows(sixam_de, sevenam_de, eightam_de)
gotowork_as <- bind_rows(sixam_as, sevenam_as, eightam_as)
gohome_de <- bind_rows(fivepm_de, sixpm_de, sevenpm_de)
gohome_as <- bind_rows(fivepm_as, sixpm_as, sevenpm_as)

table(droplevels(gotowork_as$노선명))
