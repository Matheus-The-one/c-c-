#include <stdio.h>
#define MAX_CLIENTS 1000
#define MAX_SERVICE_POINTS 1000

int main() {
  int t;
  scanf("%d", &t);
  while (t--) {
    int m, k, n = 0, max_served = 0, latest_finish_time = 0;
    scanf("%d %d", &m, &k);
    int ready_time[MAX_SERVICE_POINTS] = {0};
    while (scanf("%d %d", &r, &p) == 2) {
      int best_service_point = 0;
      for (int i = 1; i <= m; i++) {
        if (ready_time[i] < ready_time[best_service_point]) {
          best_service_point = i;
        }
      }
      if (ready_time[best_service_point] + p <= k) {
        ready_time[best_service_point] += p;
        n++;
        if (ready_time[best_service_point] > latest_finish_time) {
          latest_finish_time = ready_time[best_service_point];
        }
      }
    }
    printf("%d %d\n", n, latest_finish_time);
  }
  return 0;
}


