# 🛡️ AFES - Advanced Fire Emergency System

AFES is a professional real-time fire monitoring and alert dashboard. It leverages IoT sensor data (temperature, smoke, etc.) to provide instant safety status updates and emergency notifications.

The system architecture follows a modern Fullstack approach with a fully decoupled Frontend and Backend.

## 🏗️ System Architecture

This repository acts as the master orchestrator, managing the entire lifecycle of the AFES project through containerization.

```text
AFES/ 
├── frontend/           # React + Vite (Dashboard UI) 
├── backend/            # Java Spring Boot (REST API & Business Logic) 
├── docker-compose.yml 
└── README.md
'''
## 🚀 Local Development & Testing

The project is fully Dockerized. You can launch the entire stack (Frontend + Backend) with a single command — no need to install Java or Node.js locally.

### 📋 Prerequisites

- Docker
- Docker Compose
- Git

---

## 🛠️ Quick Start

### 1️⃣ Clone the repository (including submodules)

```bash
git clone --recursive https://github.com/Huyhuy225/AFES.git
cd AFES
'''

