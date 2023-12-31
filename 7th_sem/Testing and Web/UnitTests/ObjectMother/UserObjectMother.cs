using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using mbti_web.Entities;

namespace UnitTests.ObjectMother
{
    // guid new guid
    public class UserObjectMother
    {
        public User UnauthorizedUser()
        {
            User user = new User(8753, "", "", "", "", "", 1, DateTime.Now);
            return user;
        }
        public User AuthorizedUser()
        {
            User user = new User();
            user.Useruk = Guid.NewGuid().GetHashCode();
            user.Login = Guid.NewGuid().ToString();
            user.Password = "password";
            user.Email = "email";
            user.Telagram = "telegram";
            user.Nickname = "user";
            user.Dateofbirth = DateTime.Today;
            user.Typeuk = 1;
            return user;
        }
        public User ExistingUserHerrington()
        {
            User user = new User();
            user.Useruk = 1;
            user.Nickname = "BillyHerrington";
            user.Login = "BillyHerrington";
            user.Password = "123";
            user.Email = "BillyHerrington@gmail.com";
            user.Telagram = "@BillyHerrington";
            user.Typeuk = 8;
            user.Dateofbirth = DateTime.ParseExact("1969-07-14", "yyyy-MM-dd",
                                       System.Globalization.CultureInfo.InvariantCulture);

            return user;
        }
        public User ExistingUserDarkholme()
        {
            User user = new User();
            user.Useruk = 4;
            user.Nickname = "VanDarkholme";
            user.Login = "VanDarkholme";
            user.Password = "1234";
            user.Email = "VanDarkholme@gmail.com";
            user.Telagram = "@VanDarkholme";
            user.Typeuk = 7;
            user.Dateofbirth = DateTime.ParseExact("1972-10-24", "yyyy-MM-dd",
                                       System.Globalization.CultureInfo.InvariantCulture);

            return user;
        }
        public User TestUser()
        {
            User user = new User();
            user.Useruk = Guid.NewGuid().GetHashCode();
            user.Login = Guid.NewGuid().ToString();
            user.Password = "testpassword";
            user.Email = "testemail";
            user.Telagram = "testtelegram";
            user.Nickname = "testuser";
            user.Dateofbirth = DateTime.Today;
            user.Typeuk = 1;
            return user;
        }
        public User UserForDelete()
        {
            User user = new User();
            user.Useruk = 100000;
            user.Login = Guid.NewGuid().ToString();
            user.Password = "password";
            user.Email = "email";
            user.Telagram = "telegram";
            user.Nickname = "deleteuser";
            user.Dateofbirth = DateTime.Today;
            user.Typeuk = 1;
            return user;
        }
    }
}
