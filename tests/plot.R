setwd("/home/apm/git/sa_3sat/tests")

require(ggplot2)
require(grid)
require(gridExtra)

plotta<-function()
{
  a <- c()
  fv <- c()
  
  for (i in 1:10) {
    a[[i]] <- data.frame(read.table(paste("runs/teste", i, ".txt", sep=""), header=FALSE))
    fv[i]<-max(a[[i]][,2])
    print(max(a[[i]][,2]))
  }
  print(sd(fv))
  print(mean(fv))
  b <- a[[1]]
  for (i in 2:10) {
    b <- b + a[[i]];
  }
  
  b <- b[,2] / 10;
  plot(b, type="l", xlab="Iteração", ylab="Cláusulas")
  
}
plotta()




a <- data.frame(read.table("testes.txt", header=FALSE))
plot(a[,2])

plot(b, type="l")

