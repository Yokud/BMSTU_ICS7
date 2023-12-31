﻿using System.ComponentModel.DataAnnotations;

namespace mbti_web.Models
{
    public class AuthenticateRequest
    {
        [Required]
        public string Login { get; set; }

        [Required]
        public string Password { get; set; }
        public AuthenticateRequest() { }
        public AuthenticateRequest(string login, string password)
        {
            Login = login;
            Password = password;
        }
    }
}
