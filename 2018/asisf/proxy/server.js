const express = require('express');
const fs = require('fs');
const path = require('path');
const body_parser = require('body-parser');
const md5 = require('md5');
const http = require('http');
var ip = require("ip");
require('x-date');
var server_ip = ip.address() 
const server = express();
server.use(body_parser.urlencoded({
  extended: true
}));
server.use(express.static('public')) 
server.set('views', path.join(__dirname, 'views'));
server.set('view engine', 'jade');
server.listen(5000) 
server.get('/', function(request, result) {
  result.render('index');
  result.end()
})
function check_endpoint(available_endpoints, endpoint) {
  for (i of available_endpoints) {
    if (endpoint.indexOf(i) == 0) {
      return true;
    }
  }
  return false;
}
fs.readFile('flag.dat', 'utf8', function(err, contents) {
  if (err) {
    throw err;
  }
  flag = contents;
}) 
server.get('/proxy/internal_website/:page', function(request, result) {
  var available_endpoints = ['public_notes', 'public_links', 'source_code']
  var page = request.params.page 
  //result.setHeader('X-Node-js-Version', 'v8.12.0') 
  //result.setHeader('X-Express-Version', 'v4.16.3') 
  if (page.toLowerCase().includes('flag')) {
    result.sendStatus(403) 
    result.end()
  } else if (!check_endpoint(available_endpoints, page)) {
    result.render('available_endpoints', {
      endpoints: JSON.stringify(available_endpoints)
    })
    result.end()
  } else {
    http.get('http://127.0.0.1:5000/' + page, function(res) {
      res.setEncoding('utf8');
      if (res.statusCode == 200) {
        res.on('data', function(chunk) {
          result.render('proxy', {
            contents: chunk
          }) 
          result.end()
        });
      } else if (res.statusCode == 404) {
        result.render('proxy', {
          contents: 'The resource not found.'
        }) 
        result.end()
      } else {
        result.end()
      }
    }).on('error', function(e) {
      console.log("Got error: " + e.message);
    });
  }
}) 
server.use(function(request, result, next) {
  ip = request.connection.remoteAddress
  if (ip.substr(0, 7) == "::ffff:") {
    ip = ip.substr(7)
  }
  if (ip != '127.0.0.1' && ip != server_ip) {
    result.render('unauthorized') 
    result.end()
  } else {
    next()
  }
}) 
server.get('/public_notes', function(request, result) {
  result.render('public_notes');
  result.end()
})
server.get('/public_links', function(request, result) {
  result.render('public_links');
  result.end()
})
server.get('/source_code', function(request, result) {
  fs.readFile('server.js', 'utf8', function(err, contents) {
    if (err) {
      throw err;
    }
    result.render('source_code', {
      source: contents
    }) 
    result.end()
  })
})
server.get('/flag/:token', function(request, result) {
  var token = request.params.token
  if (token.length > 10) {
    console.log(ip) 
    fs.writeFile('public/temp/' + md5(ip + token), flag, (err) => {
      if (err) throw err;
      result.end();
    });
  }
})
server.get('/', function(request, result) {
  result.render('index');
  result.end()
})
server.get('*', function(req, result) {
  result.sendStatus(404);
  result.end()
});
