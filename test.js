var iDR = require('./lib/RoutonRead');

//var cardInfo = iDR.readCard();
// if(cardInfo)
// {
// console.log('姓名:', cardInfo.name);
// console.log('性别:', cardInfo.gender);
// console.log('民族:', cardInfo.folk);
// console.log('生日:', cardInfo.birthDay);
// console.log('身份证号码:', cardInfo.code);
// console.log('地址:', cardInfo.address);
// console.log('签证机关:', cardInfo.agency);
// console.log('有效期起始日期:', cardInfo.expireStart);
// console.log('有效期截至日期:', cardInfo.expireEnd);
// }
// else{
// console.log('读取身份证信息失败！');
// }
try {
	var result = iDR.openRealReadCard(1001, function (cardInfo) {
		if (cardInfo.cardType == 1) {
			console.log('姓名:', cardInfo.name);
			console.log('性别:', cardInfo.gender);
			console.log('民族:', cardInfo.folk);
			console.log('生日:', cardInfo.birthDay);
			console.log('身份证号码:', cardInfo.code);
			console.log('地址:', cardInfo.address);
			console.log('签证机关:', cardInfo.agency);
			console.log('有效期起始日期:', cardInfo.expireStart);
			console.log('有效期截至日期:', cardInfo.expireEnd);
		}
		else {
			console.log('卡号:', cardInfo.code);
		}
	}, function (err) {
		console.log('读取卡信息失败——', err);
	});

	console.log('初始化读卡设备：', result ? '成功' : '失败');

	if (result) result = iDR.startRealReadCard();
	console.log('开始读卡：', result ? '成功' : '失败');

	setTimeout(function () {
		if (result) result = iDR.stopRealReadCard();
		console.log('暂停读卡：', result ? '成功' : '失败');
	}, 20000);
} catch (error) {
	console.info(error);
}

process.on('uncaughtException', function (err) {
	console.log(err);
});

process.stdin.resume();
