# CSA0413 - Operating Systems: Assignment 5 (CO5)
**Title:** Linux, Containers and Virtualisation for Efficient Operations (Total Marks - 50)  
**Student Name:** M.V. Rakesh Reddy  
**Register Number:** 19524164  
**Department:** Artificial Intelligence and Data Science (AI & DS)  
**Course & Code:** Operating Systems (CSA0413)  
**Course Faculty:** Kruthika K  
**Submission Date:** 17-11-2026  
**Environment:** Debian 12 (Bookworm) / Linux 6.12.105+ x86_64 | Docker | Kubernetes  
**GitHub Repository Link:** https://github.com/Rakeshreddymeruva/CSA0413-OS/tree/main/CO5  

---

## Directory Structure
```
CO5/
├── README.md
├── TaskB1/
│   ├── log_analyzer.sh
│   ├── disk_alert.sh
│   ├── result-portal.service
│   └── nginx-portal.conf
├── TaskB2/
│   ├── app.py
│   ├── requirements.txt
│   ├── Dockerfile
│   └── docker-compose.yml
├── TaskB3/
│   └── deployment.yaml
└── TaskB4/
    └── docker-compose-extended.yml
```

---

## Execution & Deployment Instructions
```bash
# Task B1: Run Log Analyzer & Disk Alert
bash TaskB1/log_analyzer.sh
bash TaskB1/disk_alert.sh

# Task B2: Build and run Docker Container (non-root user 'portal')
cd TaskB2
docker build -t result-portal .
docker run -d -p 8000:8000 --cpus="0.5" --memory="512m" --name portal-app result-portal
docker exec portal-app whoami   # outputs: portal

# Task B3: Deploy to Kubernetes (3 replicas, resource requests/limits, LoadBalancer)
kubectl apply -f TaskB3/deployment.yaml
kubectl get pods -l app=result-portal
kubectl describe pod -l app=result-portal

# Task B4: Multi-service Compose (Portal + LMS/Exam Service)
docker compose -f TaskB4/docker-compose-extended.yml up -d
```

---

## Verified Execution Outputs

### Task B1: `log_analyzer.sh` Output
```
Requests per status code:
200 4
302 1
403 1
404 1
Busiest client:
10.0.0.5 4
Total bytes sent: 43200
```
