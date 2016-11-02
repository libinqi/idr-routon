var addon = require('../bin/RoutonRead.node');
var routonRead = new addon.RoutonRead();

exports.readCard = function (port) {
    port = port || 1001;
    var result = routonRead.InitComm(port);
    if (result) {
        result = routonRead.Authenticate();
        if (result) {
            result = routonRead.ReadBaseInfos();
            if (result) {
                routonRead.ShutDownAntenna();
                routonRead.CloseComm();
                return result;
            }

        }
    }
    return 0;
};

exports.startRealReadCard = function (port, realCallback, errorCallback) {
    port = port || 1001;
    var result = routonRead.StartRealReadCard(port, realCallback, errorCallback);
    return result;
};

exports.stopRealReadCard = function () {
    var result = routonRead.StopRealReadCard();
    return result;
};

