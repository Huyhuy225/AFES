# Kubernetes Deployment for AFES (Minikube)

## Cấu trúc thư mục
```
k8s/
├── namespace.yaml              # Tạo namespace "afes"
├── configmap.yaml              # Config cho tất cả services
├── secret.yaml                 # Mật khẩu và credentials
├── mysql-pvc.yaml              # Persistent Volume Claim cho MySQL
├── mysql-deployment.yaml       # MySQL + Service
├── mosquitto-deployment.yaml   # Mosquitto MQTT + Service
├── backend-deployment.yaml     # Backend Spring Boot + Service
├── frontend-deployment.yaml    # Frontend Nginx + Service
└── README-K8S.md               # File này
```

## Hướng dẫn triển khai

### 1. Chuẩn bị Minikube
```bash
# Khởi động minikube
minikube start --cpus=4 --memory=4096

# Enable addons (nếu cần)
minikube addons enable ingress
```

### 2. Build Docker images cho Minikube
```bash
# Đảm bảo Docker daemon của minikube được sử dụng
eval $(minikube docker-env)

# Build các images
docker-compose build

# Hoặc build riêng từng service
docker build -t afes-backend:latest ./backend
docker build -t afes-frontend:latest ./frontend
```

### 3. Deploy lên K8s
```bash
# Áp dụng tất cả manifests (theo thứ tự)
kubectl apply -f k8s/namespace.yaml
kubectl apply -f k8s/configmap.yaml
kubectl apply -f k8s/secret.yaml
kubectl apply -f k8s/mysql-pvc.yaml
kubectl apply -f k8s/mysql-deployment.yaml
kubectl apply -f k8s/mosquitto-deployment.yaml
kubectl apply -f k8s/backend-deployment.yaml
kubectl apply -f k8s/frontend-deployment.yaml

# Hoặc cùng lúc
kubectl apply -f k8s/
```

### 4. Kiểm tra trạng thái
```bash
# Xem tất cả pods
kubectl get pods -n afes

# Xem chi tiết pod
kubectl describe pod <pod-name> -n afes

# Xem logs
kubectl logs <pod-name> -n afes

# Xem services
kubectl get svc -n afes
```

### 5. Truy cập ứng dụng
```bash
# Lấy URL của frontend (NodePort)
minikube service frontend-service -n afes --url

# Hoặc trực tiếp
minikube service frontend-service -n afes
```

## Thay đổi cấu hình

### Để cập nhật environment variables:
Edit `configmap.yaml` và chạy:
```bash
kubectl apply -f k8s/configmap.yaml
# Restart pods để load lại config
kubectl rollout restart deployment/backend -n afes
```

### Để cập nhật mật khẩu:
Edit `secret.yaml` và chạy:
```bash
kubectl apply -f k8s/secret.yaml
# Restart pods
kubectl rollout restart deployment/backend -n afes
```

## Xóa tất cả resources
```bash
kubectl delete namespace afes
```

## Notes
- Minikube sử dụng local docker images, nên `imagePullPolicy: Never`
- MySQL data được lưu trong PVC, sẽ persist khi pod restart
- Để expose frontend ra ngoài, dùng `minikube tunnel` hoặc port-forward
- Backend tự động chờ MySQL sẵn sàng trước khi start (init container)
