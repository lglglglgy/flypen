// mysql
#include "jdbc/mysql_driver.h"
#include <jdbc/mysql_connection.h>
#include "mysql.h"
#include <jdbc/cppconn/prepared_statement.h>
void sql_add(std::string username, std::string passwd)
{
    try
    {
        sql::mysql::MySQL_Driver *driver;
        driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection *con;
        con = driver->connect("tcp://192.168.31.78:3306", "root", "abc.123");
        con->setSchema("flypen");
        sql::Statement *tool;
        tool = con->createStatement();
        std::string classmysql = "INSERT INTO  users(username, password,createtime) VALUES (?, ? ,0)";
        sql::PreparedStatement *ptool = con->prepareStatement(classmysql);
        ptool->setString(1, username);
        ptool->setString(2, passwd);
        ptool->executeUpdate();
        delete ptool;
        delete tool;
        delete con;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    }
}
bool sql_check(std::string value)
{
    bool result = false;
    try
    {
        
        sql::mysql::MySQL_Driver *driver;
        driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection *con;
        con = driver->connect("tcp://192.168.31.78:3306", "root", "abc.123");
        con->setSchema("flypen");
        std::string sql = "SELECT * FROM users WHERE username = ? LIMIT 1";
        sql::PreparedStatement *prepStmt = con->prepareStatement(sql);
        prepStmt->setString(1, value);
        sql::ResultSet *res = prepStmt->executeQuery();

        // 获取查询结果
        if (!(res->next()))
        {
            result = true;
            // 提取所有列的值
            std::string username = res->getString("username");
            std::string password = res->getString("password");
            int createtime = res->getInt("createtime");

            // 在这里输出或使用提取的值
            std::cout << "Username: " << username << std::endl;
            std::cout << "Password: " << password << std::endl;
            std::cout << "CreateTime: " << createtime << std::endl;
        }

        delete res;
        delete prepStmt;
        delete con;
    }
    catch (sql::SQLException &e)
    {
      //  std::cerr << "SQL Exception: " << e.what() << std::endl;
    }

    return result;
}
bool sql_check(std::string value,std::string passwd)
{
    bool result = false;
    try
    {
        
        sql::mysql::MySQL_Driver *driver;
        driver = sql::mysql::get_mysql_driver_instance();
        sql::Connection *con;
        con = driver->connect("tcp://192.168.31.78:3306", "root", "abc.123");
        con->setSchema("flypen");
        std::string sql = "SELECT * FROM users WHERE username = ? LIMIT 1";
        sql::PreparedStatement *prepStmt = con->prepareStatement(sql);
        prepStmt->setString(1, value);
        sql::ResultSet *res = prepStmt->executeQuery();

        // 获取查询结果
        if ((res->next()))
        {
            //result = true;
            // 提取所有列的值
            std::string username = res->getString("username");
            std::string password = res->getString("password");
            int createtime = res->getInt("createtime");
            if(password==passwd) result = true;

            // 在这里输出或使用提取的值
            std::cout << "Username: " << username << std::endl;
            std::cout << "Password: " << password << std::endl;
            std::cout << "CreateTime: " << createtime << std::endl;
        }

        delete res;
        delete prepStmt;
        delete con;
    }
    catch (sql::SQLException &e)
    {
        std::cerr << "SQL Exception: " << e.what() << std::endl;
    }

    return result;
}
//编程练习2.6
//1.使用elis
//cpp