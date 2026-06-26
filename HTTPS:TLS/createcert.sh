#!/bin/bash 

# Create private-key 

openssl genrsa -out private-key.pem 2048

# Create certificate and self sign it wiht private key

openssl req -new -x509 -key private-key.pem -out certificate.pem -days 365

