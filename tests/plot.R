setwd("/home/apm/git/sa_3sat/tests")

require(ggplot2)
require(grid)
require(gridExtra)

a <- c()

for (i in 1:10) {
  a[[i]] <- data.frame(read.table(paste("runs/teste", i, ".txt", sep=""), header=FALSE))
}

b <- a[[1]]
for (i in 2:10) {
  b <- b + a[[i]];
}

b <- b[,2] / 10;
plot(b, type="l")

a <- data.frame(read.table("testes.txt", header=FALSE))
plot(a[,2])

plot(b, type="l")

