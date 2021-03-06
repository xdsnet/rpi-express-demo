var express = require('express');
var router = express.Router();
var net = require('net');

var PORT = 5555;
/* 具体路由模块实现. */
router.get('/', function(req, res, next) {
  // 实现逻辑
  var revData='';
  var client = net.connect({port:PORT},function(){
    console.log('连接到服务器');
  });
  client.on('data',function(data){
    revData=data.toString();
    console.log(data.toString());
    res.send(revData);
    client.end();
  });
  client.on('end',function(){
    console.log('断开与服务器的连接');
  });
  client.write("off");
 // client.write("quit");
  //res.send('respond with a resource');
});

module.exports = router;
