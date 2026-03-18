#include<aws/s3/S3Client.h>
#include<aws/s3/model/GetObjectRequest.h>
#include<aws/s3/model/GetObjectResult.h>
#include<aws/s3/model/PutObjectRequest.h>
#include<aws/s3/model/PutObjectResult.h>
#include<aws/s3/model/DeleteObjectRequest.h>
#include<aws/s3/model/DeleteObjectResult.h>

std::string getSignedUrl(const std::string& key);
std::string putObjectSignedUrl(const std::string& key);
bool deleteObject(const std::string& key);
std::string urlToKey(const std::string& url);