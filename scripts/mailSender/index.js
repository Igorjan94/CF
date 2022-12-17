const nodemailer = require('nodemailer');
const smtpTransport = require('nodemailer-smtp-transport');
const config = require('./config.json');
const transporter = nodemailer.createTransport(smtpTransport(config.emailSettings));
const process = require('process');
const args = process.argv.slice(2);

//Config contains:
//{
  //"emailSettings": {
    //"domains": [
      //"yandex.ru"
    //],
    //"host": "smtp.yandex.ru",
    //"secureConnection": true,
    //"port": 465,
    //"auth": {
      //"user": "username@yandex.ru",
      //"pass": "pAsSwOrD"
    //}
  //}
//} 

let sendEmail = async (to, header, html) => {
    console.log(`Sending mail to ${to}:\n${header}`);
    if (!to)
        return;

    let mailOptions = {
        from: '"Зайка Познайка" <zaikapoznaika@yandex.ru>',
        to: to,
        subject: header,
        html: html
    };

    await transporter.sendMail(mailOptions, (error, info) => {
        if (error) {
            console.error(error);
        } else
            console.log(info);
    });
    console.log(`email to ${to} is successfully sent`);
}

if (args.length < 2)
    console.error('Not enough arguments\nUsage: node index.js igorjan94@mail.ru theme text');
else
    sendEmail(args[0], args[1], args[2] || '');

module.exports = {
    sendEmail: sendEmail
};
